/*
 * Copyright 2021 Google LLC
 * SPDX-License-Identifier: MIT
 */

#include "vkr_ring.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "util/u_math.h"

#include "virgl_context.h"

enum vkr_ring_status_flag {
   VKR_RING_STATUS_IDLE = 1u << 0,
};

static void
vkr_ring_store_head(struct vkr_ring *ring)
{
   /* the renderer is expected to load the head with memory_order_acquire,
    * forming a release-acquire ordering
    */
   atomic_store_explicit(ring->shared.head, ring->cur, memory_order_release);
}

static uint32_t
vkr_ring_load_tail(const struct vkr_ring *ring)
{
   /* the driver is expected to store the tail with memory_order_release,
    * forming a release-acquire ordering
    */
   return atomic_load_explicit(ring->shared.tail, memory_order_acquire);
}

static void
vkr_ring_store_status(struct vkr_ring *ring, uint32_t status)
{
   atomic_store_explicit(ring->shared.status, status, memory_order_seq_cst);
}

static void
vkr_ring_read_buffer(struct vkr_ring *ring, void *data, size_t size)
{
   const size_t offset = ring->cur & ring->buffer_mask;
   assert(size <= ring->buffer_size);
   if (offset + size <= ring->buffer_size) {
      memcpy(data, (const uint8_t *)ring->shared.buffer + offset, size);
   } else {
      const size_t s = ring->buffer_size - offset;
      memcpy(data, (const uint8_t *)ring->shared.buffer + offset, s);
      memcpy((uint8_t *)data + s, ring->shared.buffer, size - s);
   }

   ring->cur += size;
}

struct vkr_ring *
vkr_ring_create(const struct vkr_ring_layout *layout,
                void *shared,
                struct virgl_context *ctx,
                uint64_t idle_timeout)
{
   struct vkr_ring *ring;
   int ret;

   ring = calloc(1, sizeof(*ring));
   if (!ring)
      return NULL;

   ring->shared.head = (void *)((uint8_t *)shared + layout->head_offset);
   ring->shared.tail = (void *)((uint8_t *)shared + layout->tail_offset);
   ring->shared.status = (void *)((uint8_t *)shared + layout->status_offset);
   ring->shared.buffer = (void *)((uint8_t *)shared + layout->buffer_offset);
   ring->shared.extra = (void *)((uint8_t *)shared + layout->extra_offset);

   assert(layout->buffer_size && util_is_power_of_two(layout->buffer_size));
   ring->buffer_size = layout->buffer_size;
   ring->buffer_mask = layout->buffer_size - 1;
   ring->extra_size = layout->extra_size;

   /* we will manage head and status, and we expect them to be 0 initially */
   if (*ring->shared.head || *ring->shared.status) {
      free(ring);
      return NULL;
   }

   ring->cmd = malloc(ring->buffer_size);
   if (!ring->cmd) {
      free(ring);
      return NULL;
   }

   ring->context = ctx;
   ring->idle_timeout = idle_timeout;

   ret = mtx_init(&ring->mutex, mtx_plain);
   if (ret != thrd_success) {
      free(ring->cmd);
      free(ring);
      return NULL;
   }
   ret = cnd_init(&ring->cond);
   if (ret != thrd_success) {
      mtx_destroy(&ring->mutex);
      free(ring->cmd);
      free(ring);
      return NULL;
   }

   ring->join = true;

   return ring;
}

void
vkr_ring_destroy(struct vkr_ring *ring)
{
   assert(ring->join);
   mtx_destroy(&ring->mutex);
   cnd_destroy(&ring->cond);
   free(ring->cmd);
   free(ring);
}

static uint64_t
vkr_ring_now(void)
{
   const uint64_t ns_per_sec = 1000000000llu;
   struct timespec now;
   if (clock_gettime(CLOCK_MONOTONIC, &now))
      return 0;
   return ns_per_sec * now.tv_sec + now.tv_nsec;
}

static void
vkr_ring_relax(void)
{
   /* TODO do better */
   thrd_yield();
}

static int
vkr_ring_thread(void *arg)
{
   struct vkr_ring *ring = arg;
   struct virgl_context *ctx = ring->context;
   uint64_t last_submit = vkr_ring_now();
   int ret = 0;

   while (!ring->join) {
      bool wait = false;
      uint32_t cmd_size;

      if (vkr_ring_now() >= last_submit + ring->idle_timeout) {
         ring->pending_notify = false;
         vkr_ring_store_status(ring, VKR_RING_STATUS_IDLE);
         wait = ring->cur == vkr_ring_load_tail(ring);
         if (!wait)
            vkr_ring_store_status(ring, 0);
      }

      if (wait) {
         mtx_lock(&ring->mutex);
         if (!ring->join && !ring->pending_notify)
            cnd_wait(&ring->cond, &ring->mutex);
         vkr_ring_store_status(ring, 0);
         mtx_unlock(&ring->mutex);

         if (ring->join)
            break;
      }

      cmd_size = vkr_ring_load_tail(ring) - ring->cur;
      if (cmd_size) {
         if (cmd_size > ring->buffer_size) {
            ret = -EINVAL;
            break;
         }

         vkr_ring_read_buffer(ring, ring->cmd, cmd_size);
         ctx->submit_cmd(ctx, ring->cmd, cmd_size);
         vkr_ring_store_head(ring);

         last_submit = vkr_ring_now();
      } else {
         vkr_ring_relax();
      }
   }

   return ret;
}

void
vkr_ring_start(struct vkr_ring *ring)
{
   int ret;

   assert(ring->join);
   ring->join = false;
   ret = thrd_create(&ring->thread, vkr_ring_thread, ring);
   if (ret != thrd_success)
      ring->join = true;
}

bool
vkr_ring_stop(struct vkr_ring *ring)
{
   mtx_lock(&ring->mutex);
   if (ring->thread == thrd_current()) {
      mtx_unlock(&ring->mutex);
      return false;
   }
   assert(!ring->join);
   ring->join = true;
   cnd_signal(&ring->cond);
   mtx_unlock(&ring->mutex);

   thrd_join(ring->thread, NULL);

   return true;
}

void
vkr_ring_notify(struct vkr_ring *ring)
{
   mtx_lock(&ring->mutex);
   ring->pending_notify = true;
   cnd_signal(&ring->cond);
   mtx_unlock(&ring->mutex);
}

bool
vkr_ring_write_extra(struct vkr_ring *ring, size_t offset, uint32_t val)
{
   if (offset > ring->extra_size || sizeof(val) > ring->extra_size - offset)
      return false;

   volatile atomic_uint *dst =
      (void *)((uint8_t *)ring->shared.extra + offset);
   atomic_store_explicit(dst, val, memory_order_release);

   return true;
}
