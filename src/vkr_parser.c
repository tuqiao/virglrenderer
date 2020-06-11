/*
 * Copyright 2019 Google LLC
 *
 * based in part on anv driver which is:
 * Copyright © 2015 Intel Corporation
 * Copyright © 2016 Red Hat.
 * Copyright © 2016 Bas Nieuwenhuizen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "vkr_parser.h"

static uint32_t
grow_array_size(uint32_t size,
                uint32_t used,
                uint32_t growth,
                uint32_t min_size)
{
   assert(size >= used && min_size);
   if (!size)
      size = min_size;

   uint32_t new_size = size;
   while (new_size - used < growth) {
      new_size *= 2;
      if (new_size < size)
         return 0;
   }
   return new_size;
}

static size_t
grow_buffer_size(size_t size, size_t used, size_t growth, size_t min_size)
{
   assert(size >= used && min_size);
   if (!size)
      size = min_size;

   size_t new_size = size;
   while (new_size - used < growth) {
      new_size *= 2;
      if (new_size < size)
         return 0;
   }
   return new_size;
}

void
vkr_parser_init(struct vkr_parser *parser,
                struct util_hash_table_u64 *object_table)
{
   memset(parser, 0, sizeof(*parser));
   parser->object_table = object_table;
}

void
vkr_parser_fini(struct vkr_parser *parser)
{
   struct vkr_parser_temp_pool *pool = &parser->temp_pool;
   for (uint32_t i = 0; i < pool->buffer_count; i++)
      free(pool->buffers[i]);
   if (pool->buffers)
      free(pool->buffers);
}

/**
 * Reset a parser for reuse.
 */
void
vkr_parser_reset(struct vkr_parser *parser)
{
   parser->error = false;

   struct vkr_parser_temp_pool *pool = &parser->temp_pool;
   if (pool->buffer_count) {
      /* free all but the last buffer */
      for (uint32_t i = 0; i < pool->buffer_count - 1; i++)
         free(pool->buffers[i]);

      pool->buffers[0] = pool->buffers[pool->buffer_count - 1];
      pool->buffer_count = 1;

      assert(pool->cur >= pool->buffers[0]);
      pool->cur = pool->buffers[0];
   }

   parser->command.cur = NULL;
   parser->command.end = NULL;

   parser->reply.remaining_size = 0;
   parser->reply.next_iov = 0;
   parser->reply.cur = NULL;
   parser->reply.end = NULL;
}

static bool
vkr_parser_grow_temp_pool(struct vkr_parser *parser)
{
   struct vkr_parser_temp_pool *pool = &parser->temp_pool;
   const uint32_t buffer_max =
      grow_array_size(pool->buffer_max, pool->buffer_count, 1, 4);
   if (!buffer_max)
      return false;

   uint8_t **buffers = realloc(pool->buffers, sizeof(*pool->buffers) * buffer_max);
   if (!buffers)
      return false;

   pool->buffers = buffers;
   pool->buffer_max = buffer_max;

   return true;
}

bool
vkr_parser_alloc_temp_internal(struct vkr_parser *parser, size_t size)
{
   struct vkr_parser_temp_pool *pool = &parser->temp_pool;

   if (pool->buffer_count >= pool->buffer_max) {
      if (!vkr_parser_grow_temp_pool(parser))
         return false;
      assert(pool->buffer_count < pool->buffer_max);
   }

   const size_t last_buffer_size =
      pool->buffer_count ? pool->end - pool->buffers[pool->buffer_count - 1]
                         : 0;
   const size_t buffer_size = grow_buffer_size(
      last_buffer_size, last_buffer_size, size, 4096);
   if (!buffer_size)
      return false;

   uint8_t *buffer = malloc(buffer_size);
   if (!buffer)
      return false;

   pool->buffers[pool->buffer_count++] = buffer;
   pool->cur = buffer;
   pool->end = buffer + buffer_size;

   return true;
}

void
vkr_parser_set_command_stream(struct vkr_parser *parser,
                              const void *data,
                              size_t size)
{
   parser->command.cur = data;
   parser->command.end = parser->command.cur + size;
}

void
vkr_parser_set_reply_stream(struct vkr_parser *parser,
                            const struct iovec *iov,
                            int iov_count,
                            size_t offset,
                            size_t size)
{
   parser->reply.iov = iov;
   parser->reply.iov_count = iov_count;
   parser->reply.offset = offset;
   parser->reply.size = size;

   /* clear cache */
   parser->reply.cached_index = 0;
   parser->reply.cached_offset = 0;

   vkr_parser_seek_reply_stream(parser, 0);
}

static bool
vkr_parser_translate_reply_stream_offset(struct vkr_parser *parser,
                                         size_t offset,
                                         int *iov_index,
                                         size_t *iov_offset)
{
   int idx = 0;

   /* use or clear cache */
   if (offset >= parser->reply.cached_offset) {
      offset -= parser->reply.cached_offset;
      idx = parser->reply.cached_index;
   } else {
      parser->reply.cached_index = 0;
      parser->reply.cached_offset = 0;
   }

   while (true) {
      if (idx >= parser->reply.iov_count)
         return false;

      const struct iovec *iov = &parser->reply.iov[idx];
      if (offset < iov->iov_len)
         break;

      idx++;
      offset -= iov->iov_len;

      /* update cache */
      parser->reply.cached_index++;
      parser->reply.cached_offset += iov->iov_len;
   }

   *iov_index = idx;
   *iov_offset = offset;

   return true;
}

static void
vkr_parser_update_reply_stream_end(struct vkr_parser *parser)
{
   const struct iovec *iov = &parser->reply.iov[parser->reply.next_iov - 1];
   const size_t iov_offset = parser->reply.cur - (uint8_t *)iov->iov_base;
   const size_t iov_remain = iov->iov_len - iov_offset;

   if (parser->reply.remaining_size >= iov_remain) {
      parser->reply.end = parser->reply.cur + iov_remain;
      parser->reply.remaining_size -= iov_remain;
   } else {
      parser->reply.end = parser->reply.cur + parser->reply.remaining_size;
      parser->reply.remaining_size = 0;
   }
}

void
vkr_parser_seek_reply_stream(struct vkr_parser *parser, size_t pos)
{
   const size_t offset = parser->reply.offset + pos;
   int iov_index;
   size_t iov_offset;
   if (pos > parser->reply.size ||
       !vkr_parser_translate_reply_stream_offset(parser,
                                                 offset,
                                                 &iov_index,
                                                 &iov_offset)) {
      memset(&parser->reply, 0, sizeof(parser->reply));
      vkr_parser_set_error(parser);
      return;
   }

   parser->reply.remaining_size = parser->reply.size - pos;
   parser->reply.next_iov = iov_index + 1;

   const struct iovec *iov = &parser->reply.iov[iov_index];
   parser->reply.cur = iov->iov_base;
   parser->reply.cur += iov_offset;

   vkr_parser_update_reply_stream_end(parser);
}

static bool
vkr_parser_next_reply_stream_iov(struct vkr_parser *parser)
{
   if (parser->reply.next_iov >= parser->reply.iov_count)
      return false;

   const struct iovec *iov = &parser->reply.iov[parser->reply.next_iov++];
   parser->reply.cur = iov->iov_base;

   vkr_parser_update_reply_stream_end(parser);

   return true;
}

static uint8_t *
vkr_parser_reply_ptr(struct vkr_parser *parser, size_t size, size_t *ptr_size)
{
   do {
      uint8_t *ptr = parser->reply.cur;
      const size_t avail = parser->reply.end - parser->reply.cur;

      if (size <= avail) {
         *ptr_size = size;
         parser->reply.cur += size;
         return ptr;
      } else if (avail) {
         *ptr_size = avail;
         parser->reply.cur += avail;
         return ptr;
      }

      if (!vkr_parser_next_reply_stream_iov(parser)) {
         *ptr_size = 0;
         return NULL;
      }
   } while (true);
}

void
vkr_parser_reply_internal(struct vkr_parser *parser,
                          size_t size,
                          const void *val,
                          size_t val_size)
{
   size_t pad_size = size - val_size;

   do {
      size_t ptr_size;
      uint8_t *ptr = vkr_parser_reply_ptr(parser, val_size, &ptr_size);
      if (unlikely(!ptr)) {
         vkr_parser_set_error(parser);
         return;
      }

      memcpy(ptr, val, ptr_size);
      val = (const uint8_t *)val + ptr_size;
      val_size -= ptr_size;
   } while (val_size);

   while (pad_size) {
      size_t ptr_size;
      const void *ptr = vkr_parser_reply_ptr(parser, pad_size, &ptr_size);
      if (unlikely(!ptr)) {
         vkr_parser_set_error(parser);
         return;
      }
      pad_size -= ptr_size;
   }
}
