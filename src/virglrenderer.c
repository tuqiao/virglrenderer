/**************************************************************************
 *
 * Copyright (C) 2014 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#include <stdio.h>
#include <time.h>

#include <epoxy/gl.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "pipe/p_state.h"
#include "util/u_format.h"
#include "util/u_math.h"
#include "vkr_renderer.h"
#include "vrend_renderer.h"
#include "vrend_winsys.h"

#include "virglrenderer.h"
#include "virglrenderer_hw.h"

#include "virgl_context.h"
#include "virgl_resource.h"
#include "virgl_util.h"

struct global_state {
   bool client_initialized;
   void *cookie;
   int flags;
   const struct virgl_renderer_callbacks *cbs;

   bool resource_initialized;
   bool context_initialized;
   bool winsys_initialized;
   bool vrend_initialized;
   bool vkr_initialized;
};

static struct global_state state;

/* new API - just wrap internal API for now */

static int virgl_renderer_resource_create_internal(struct virgl_renderer_resource_create_args *args,
                                                   UNUSED struct iovec *iov, UNUSED uint32_t num_iovs,
                                                   void *image)
{
   struct virgl_resource *res;
   struct pipe_resource *pipe_res;
   struct vrend_renderer_resource_create_args vrend_args =  { 0 };

   if (!state.vrend_initialized)
      return EINVAL;

   /* do not accept handle 0 */
   if (args->handle == 0)
      return EINVAL;

   vrend_args.target = args->target;
   vrend_args.format = args->format;
   vrend_args.bind = args->bind;
   vrend_args.width = args->width;
   vrend_args.height = args->height;
   vrend_args.depth = args->depth;
   vrend_args.array_size = args->array_size;
   vrend_args.nr_samples = args->nr_samples;
   vrend_args.last_level = args->last_level;
   vrend_args.flags = args->flags;

   pipe_res = vrend_renderer_resource_create(&vrend_args, image);
   if (!pipe_res)
      return EINVAL;

   res = virgl_resource_create_from_pipe(args->handle, pipe_res, iov, num_iovs);
   if (!res) {
      vrend_renderer_resource_destroy((struct vrend_resource *)pipe_res);
      return -ENOMEM;
   }

   res->map_info = vrend_renderer_resource_get_map_info(pipe_res);

   return 0;
}

int virgl_renderer_resource_create(struct virgl_renderer_resource_create_args *args,
                                   struct iovec *iov, uint32_t num_iovs)
{
   TRACE_FUNC();
   return virgl_renderer_resource_create_internal(args, iov, num_iovs, NULL);
}

int virgl_renderer_resource_import_eglimage(struct virgl_renderer_resource_create_args *args, void *image)
{
   TRACE_FUNC();
   return virgl_renderer_resource_create_internal(args, NULL, 0, image);
}

void virgl_renderer_resource_set_priv(uint32_t res_handle, void *priv)
{
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!res)
      return;

   res->private_data = priv;
}

void *virgl_renderer_resource_get_priv(uint32_t res_handle)
{
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!res)
      return NULL;

   return res->private_data;
}

static bool detach_resource(struct virgl_context *ctx, void *data)
{
   struct virgl_resource *res = data;
   ctx->detach_resource(ctx, res);
   return true;
}

void virgl_renderer_resource_unref(uint32_t res_handle)
{
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   struct virgl_context_foreach_args args;

   if (!res)
      return;

   args.callback = detach_resource;
   args.data = res;
   virgl_context_foreach(&args);

   virgl_resource_remove(res->res_id);
}

void virgl_renderer_fill_caps(uint32_t set, uint32_t version,
                              void *caps)
{
   switch (set) {
   case VIRGL_RENDERER_CAPSET_VIRGL:
   case VIRGL_RENDERER_CAPSET_VIRGL2:
      if (state.vrend_initialized)
         vrend_renderer_fill_caps(set, version, (union virgl_caps *)caps);
      break;
   case VIRGL_RENDERER_CAPSET_VENUS:
      if (state.vkr_initialized)
         vkr_get_capset(caps);
      break;
   default:
      break;
   }
}

struct xxx_fence {
   uint32_t fence_id;
   uint32_t context_count;
   uint32_t current;
};

static void per_context_fence_retire(struct virgl_context *ctx,
                                     uint64_t queue_id,
                                     void *fence_cookie)
{
   struct xxx_fence *xxx = fence_cookie;
   xxx->current++;
   if (xxx->current == xxx->context_count) {
      state.cbs->write_fence(state.cookie, xxx->fence_id);
      free(xxx);
   }
   return;

   state.cbs->write_context_fence(state.cookie,
                                  ctx->ctx_id,
                                  queue_id,
                                  fence_cookie);
}

int virgl_renderer_context_create_with_flags(uint32_t ctx_id,
                                             uint32_t ctx_flags,
                                             uint32_t nlen,
                                             const char *name)
{
   const enum virgl_renderer_capset capset_id =
      ctx_flags & VIRGL_RENDERER_CONTEXT_FLAG_CAPSET_ID_MASK;
   struct virgl_context *ctx;
   int ret;

   TRACE_FUNC();

   /* user context id must be greater than 0 */
   if (ctx_id == 0)
      return EINVAL;

   /* unsupported flags */
   if (ctx_flags & ~VIRGL_RENDERER_CONTEXT_FLAG_CAPSET_ID_MASK)
      return EINVAL;

   ctx = virgl_context_lookup(ctx_id);
   if (ctx) {
      return ctx->capset_id == capset_id ? 0 : EINVAL;
   }

   switch (capset_id) {
   case VIRGL_RENDERER_CAPSET_VIRGL:
   case VIRGL_RENDERER_CAPSET_VIRGL2:
      if (!state.vrend_initialized)
         return EINVAL;
      ctx = vrend_renderer_context_create(ctx_id, nlen, name);
      break;
   case VIRGL_RENDERER_CAPSET_VENUS:
      if (!state.vkr_initialized)
         return EINVAL;
      ctx = vkr_context_create(nlen, name);
      break;
   default:
      return EINVAL;
      break;
   }
   if (!ctx)
      return ENOMEM;

   ctx->ctx_id = ctx_id;
   ctx->capset_id = capset_id;
   ctx->fence_retire = per_context_fence_retire;

   ret = virgl_context_add(ctx);
   if (ret) {
      ctx->destroy(ctx);
      return ret;
   }

   return 0;
}

int virgl_renderer_context_create(uint32_t handle, uint32_t nlen, const char *name)
{
   return virgl_renderer_context_create_with_flags(handle,
                                                   VIRGL_RENDERER_CAPSET_VIRGL2,
                                                   nlen,
                                                   name);
}

void virgl_renderer_context_destroy(uint32_t handle)
{
   TRACE_FUNC();
   virgl_context_remove(handle);
}

int virgl_renderer_submit_cmd(void *buffer,
                              int ctx_id,
                              int ndw)
{
   TRACE_FUNC();
   struct virgl_context *ctx = virgl_context_lookup(ctx_id);
   if (!ctx)
      return EINVAL;
   return ctx->submit_cmd(ctx, buffer, sizeof(uint32_t) * ndw);
}

int virgl_renderer_transfer_write_iov(uint32_t handle,
                                      uint32_t ctx_id,
                                      int level,
                                      uint32_t stride,
                                      uint32_t layer_stride,
                                      struct virgl_box *box,
                                      uint64_t offset,
                                      struct iovec *iovec,
                                      unsigned int iovec_cnt)
{
   TRACE_FUNC();

   struct virgl_resource *res = virgl_resource_lookup(handle);
   struct vrend_transfer_info transfer_info;

   if (!res)
      return EINVAL;

   transfer_info.level = level;
   transfer_info.stride = stride;
   transfer_info.layer_stride = layer_stride;
   transfer_info.box = (struct pipe_box *)box;
   transfer_info.offset = offset;
   transfer_info.iovec = iovec;
   transfer_info.iovec_cnt = iovec_cnt;
   transfer_info.synchronized = false;

   if (ctx_id) {
      struct virgl_context *ctx = virgl_context_lookup(ctx_id);
      if (!ctx)
         return EINVAL;

      return ctx->transfer_3d(ctx, res, &transfer_info,
                              VIRGL_TRANSFER_TO_HOST);
   } else {
      if (!res->pipe_resource)
         return EINVAL;

      return vrend_renderer_transfer_pipe(res->pipe_resource, &transfer_info,
                                          VIRGL_TRANSFER_TO_HOST);
   }
}

int virgl_renderer_transfer_read_iov(uint32_t handle, uint32_t ctx_id,
                                     uint32_t level, uint32_t stride,
                                     uint32_t layer_stride,
                                     struct virgl_box *box,
                                     uint64_t offset, struct iovec *iovec,
                                     int iovec_cnt)
{
   TRACE_FUNC();
   struct virgl_resource *res = virgl_resource_lookup(handle);
   struct vrend_transfer_info transfer_info;

   if (!res)
      return EINVAL;

   transfer_info.level = level;
   transfer_info.stride = stride;
   transfer_info.layer_stride = layer_stride;
   transfer_info.box = (struct pipe_box *)box;
   transfer_info.offset = offset;
   transfer_info.iovec = iovec;
   transfer_info.iovec_cnt = iovec_cnt;
   transfer_info.synchronized = false;

   if (ctx_id) {
      struct virgl_context *ctx = virgl_context_lookup(ctx_id);
      if (!ctx)
         return EINVAL;

      return ctx->transfer_3d(ctx, res, &transfer_info,
                              VIRGL_TRANSFER_FROM_HOST);
   } else {
      if (!res->pipe_resource)
         return EINVAL;

      return vrend_renderer_transfer_pipe(res->pipe_resource, &transfer_info,
                                          VIRGL_TRANSFER_FROM_HOST);
   }
}

int virgl_renderer_resource_attach_iov(int res_handle, struct iovec *iov,
                                       int num_iovs)
{
   TRACE_FUNC();
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!res)
      return EINVAL;

   return virgl_resource_attach_iov(res, iov, num_iovs);
}

void virgl_renderer_resource_detach_iov(int res_handle, struct iovec **iov_p, int *num_iovs_p)
{
   TRACE_FUNC();
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!res)
      return;

   if (iov_p)
      *iov_p = (struct iovec *)res->iov;
   if (num_iovs_p)
      *num_iovs_p = res->iov_count;

   virgl_resource_detach_iov(res);
}

static bool xxx_create_fence(struct virgl_context *ctx, void *data)
{
   struct xxx_fence *xxx = data;
   ctx->submit_fence(ctx, 0, 0, xxx);
   xxx->context_count++;
   return true;
}

static bool xxx_poll_fence(struct virgl_context *ctx, UNUSED void *data)
{
   ctx->retire_fences(ctx);
   return true;
}

int virgl_renderer_create_fence(int client_fence_id, UNUSED uint32_t ctx_id)
{
   TRACE_FUNC();
   const uint32_t fence_id = (uint32_t)client_fence_id;

   struct xxx_fence *xxx = calloc(1, sizeof(*xxx));
   xxx->fence_id = fence_id;

   struct virgl_context_foreach_args args;
   args.callback = xxx_create_fence;
   args.data = xxx;
   virgl_context_foreach(&args);

   return 0;
}

int virgl_renderer_context_create_fence(uint32_t ctx_id,
                                        uint32_t flags,
                                        uint64_t queue_id,
                                        void *fence_cookie)
{
   return -1;

   struct virgl_context *ctx = virgl_context_lookup(ctx_id);
   if (!ctx)
      return -EINVAL;

   return ctx->submit_fence(ctx, flags, queue_id, fence_cookie);
}

void virgl_renderer_context_poll(uint32_t ctx_id)
{
   return;

   struct virgl_context *ctx = virgl_context_lookup(ctx_id);
   if (!ctx)
      return;

   ctx->retire_fences(ctx);
}

int virgl_renderer_context_get_poll_fd(uint32_t ctx_id)
{
   struct virgl_context *ctx = virgl_context_lookup(ctx_id);
   if (!ctx)
      return -1;

   return ctx->get_fencing_fd(ctx);
}

void virgl_renderer_force_ctx_0(void)
{
   TRACE_FUNC();
   if (state.vrend_initialized)
      vrend_renderer_force_ctx_0();
}

void virgl_renderer_ctx_attach_resource(int ctx_id, int res_handle)
{
   TRACE_FUNC();
   struct virgl_context *ctx = virgl_context_lookup(ctx_id);
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!ctx || !res)
      return;
   ctx->attach_resource(ctx, res);
}

void virgl_renderer_ctx_detach_resource(int ctx_id, int res_handle)
{
   TRACE_FUNC();
   struct virgl_context *ctx = virgl_context_lookup(ctx_id);
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!ctx || !res)
      return;
   ctx->detach_resource(ctx, res);
}

int virgl_renderer_resource_get_info(int res_handle,
                                     struct virgl_renderer_resource_info *info)
{
   TRACE_FUNC();
   struct virgl_resource *res = virgl_resource_lookup(res_handle);

   if (!res || !res->pipe_resource)
      return EINVAL;
   if (!info)
      return EINVAL;

   vrend_renderer_resource_get_info(res->pipe_resource,
                                    (struct vrend_renderer_resource_info *)info);
   info->handle = res_handle;

   if (state.winsys_initialized) {
      return vrend_winsys_get_fourcc_for_texture(info->tex_id,
                                                 info->virgl_format,
                                                 &info->drm_fourcc);
   }

   return 0;
}

void virgl_renderer_get_cap_set(uint32_t cap_set, uint32_t *max_ver,
                                uint32_t *max_size)
{
   TRACE_FUNC();
   switch (cap_set) {
   case VIRGL_RENDERER_CAPSET_VIRGL:
   case VIRGL_RENDERER_CAPSET_VIRGL2:
      if (state.vrend_initialized)
         vrend_renderer_get_cap_set(cap_set, max_ver, max_size);
      break;
   case VIRGL_RENDERER_CAPSET_VENUS:
      if (state.vkr_initialized) {
         *max_ver = 0;
         *max_size = vkr_get_capset(NULL);
      }
      break;
   default:
      *max_ver = 0;
      *max_size = 0;
      break;
   }
}

void virgl_renderer_get_rect(int resource_id, struct iovec *iov, unsigned int num_iovs,
                             uint32_t offset, int x, int y, int width, int height)
{
   TRACE_FUNC();
   struct virgl_resource *res = virgl_resource_lookup(resource_id);
   if (!res || !res->pipe_resource)
      return;

   vrend_renderer_get_rect(res->pipe_resource, iov, num_iovs, offset, x, y,
                           width, height);
}


static void ctx0_fence_retire(void *fence_cookie,
                              UNUSED void *retire_data)
{
   assert(false);
   const uint32_t fence_id = (uintptr_t)fence_cookie;
   state.cbs->write_fence(state.cookie, fence_id);
}

static virgl_renderer_gl_context create_gl_context(int scanout_idx, struct virgl_gl_ctx_param *param)
{
   struct virgl_renderer_gl_ctx_param vparam;

   if (state.winsys_initialized)
      return vrend_winsys_create_context(param);

   vparam.version = 1;
   vparam.shared = param->shared;
   vparam.major_ver = param->major_ver;
   vparam.minor_ver = param->minor_ver;
   return state.cbs->create_gl_context(state.cookie, scanout_idx, &vparam);
}

static void destroy_gl_context(virgl_renderer_gl_context ctx)
{
   if (state.winsys_initialized) {
      vrend_winsys_destroy_context(ctx);
      return;
   }

   state.cbs->destroy_gl_context(state.cookie, ctx);
}

static int make_current(virgl_renderer_gl_context ctx)
{
   if (state.winsys_initialized)
      return vrend_winsys_make_context_current(ctx);

   return state.cbs->make_current(state.cookie, 0, ctx);
}

static const struct vrend_if_cbs vrend_cbs = {
   ctx0_fence_retire,
   create_gl_context,
   destroy_gl_context,
   make_current,
};

void *virgl_renderer_get_cursor_data(uint32_t resource_id, uint32_t *width, uint32_t *height)
{
   struct virgl_resource *res = virgl_resource_lookup(resource_id);
   if (!res || !res->pipe_resource)
      return NULL;

   vrend_renderer_force_ctx_0();
   return vrend_renderer_get_cursor_contents(res->pipe_resource,
                                             width,
                                             height);
}

void virgl_renderer_poll(void)
{
   TRACE_FUNC();
   struct virgl_context_foreach_args args;
   args.callback = xxx_poll_fence;
   args.data = NULL;
   virgl_context_foreach(&args);
}

void virgl_renderer_cleanup(UNUSED void *cookie)
{
   TRACE_FUNC();
   if (state.vrend_initialized)
      vrend_renderer_prepare_reset();

   if (state.context_initialized)
      virgl_context_table_cleanup();

   if (state.resource_initialized)
      virgl_resource_table_cleanup();

   if (state.vkr_initialized)
      vkr_renderer_fini();

   if (state.vrend_initialized)
      vrend_renderer_fini();

   if (state.winsys_initialized)
      vrend_winsys_cleanup();

   memset(&state, 0, sizeof(state));
}

int virgl_renderer_init(void *cookie, int flags, struct virgl_renderer_callbacks *cbs)
{
   TRACE_INIT();
   TRACE_FUNC();

   int ret;

   flags |= VIRGL_RENDERER_VENUS;

   /* VIRGL_RENDERER_THREAD_SYNC is a hint and can be silently ignored */
   if (!has_eventfd() || getenv("VIRGL_DISABLE_MT"))
      flags &= ~VIRGL_RENDERER_THREAD_SYNC;

   if (state.client_initialized && (state.cookie != cookie ||
                                    state.flags != flags ||
                                    state.cbs != cbs))
      return -EBUSY;

   if (!state.client_initialized) {
      if (cbs && (cbs->version < 1 ||
                  cbs->version > VIRGL_RENDERER_CALLBACKS_VERSION))
         return -1;

      state.cookie = cookie;
      state.flags = flags;
      state.cbs = cbs;
      state.client_initialized = true;
   }

   if (!state.resource_initialized) {
      const struct virgl_resource_pipe_callbacks *pipe_cbs =
         (flags & VIRGL_RENDERER_NO_VIRGL) ? NULL :
         vrend_renderer_get_pipe_callbacks();

      ret = virgl_resource_table_init(pipe_cbs);
      if (ret)
         goto fail;
      state.resource_initialized = true;
   }

   if (!state.context_initialized) {
      ret = virgl_context_table_init();
      if (ret)
         goto fail;
      state.context_initialized = true;
   }

   if (!state.winsys_initialized && !(flags & VIRGL_RENDERER_NO_VIRGL) &&
       (flags & (VIRGL_RENDERER_USE_EGL | VIRGL_RENDERER_USE_GLX))) {
      int drm_fd = -1;

      if (flags & VIRGL_RENDERER_USE_EGL) {
         if (cbs->version >= 2 && cbs->get_drm_fd)
            drm_fd = cbs->get_drm_fd(cookie);
      }

      ret = vrend_winsys_init(flags, drm_fd);
      if (ret) {
         if (drm_fd >= 0)
            close(drm_fd);
         goto fail;
      }
      state.winsys_initialized = true;
   }

   if (!state.vrend_initialized && !(flags & VIRGL_RENDERER_NO_VIRGL)) {
      uint32_t renderer_flags = 0;

      if (!cookie || !cbs) {
         ret = -1;
         goto fail;
      }

      if (flags & VIRGL_RENDERER_THREAD_SYNC)
         renderer_flags |= VREND_USE_THREAD_SYNC;
      if (flags & VIRGL_RENDERER_USE_EXTERNAL_BLOB)
         renderer_flags |= VREND_USE_EXTERNAL_BLOB;

      ret = vrend_renderer_init(&vrend_cbs, renderer_flags);
      if (ret)
         goto fail;
      state.vrend_initialized = true;
   }

   if (!state.vkr_initialized && (flags & VIRGL_RENDERER_VENUS)) {
      uint32_t vkr_flags = 0;
      if (flags & VIRGL_RENDERER_THREAD_SYNC)
         vkr_flags |= VKR_RENDERER_THREAD_SYNC;

      int ret = vkr_renderer_init(vkr_flags);
      if (ret)
         goto fail;
      state.vkr_initialized = true;
   }

   return 0;

fail:
   virgl_renderer_cleanup(NULL);
   return ret;
}

int virgl_renderer_get_fd_for_texture(uint32_t tex_id, int *fd)
{
   TRACE_FUNC();
   if (state.winsys_initialized)
      return vrend_winsys_get_fd_for_texture(tex_id, fd);
   return -1;
}

int virgl_renderer_get_fd_for_texture2(uint32_t tex_id, int *fd, int *stride, int *offset)
{
   TRACE_FUNC();
   if (state.winsys_initialized)
      return vrend_winsys_get_fd_for_texture2(tex_id, fd, stride, offset);
   return -1;
}

void virgl_renderer_reset(void)
{
   TRACE_FUNC();
   if (state.vrend_initialized)
      vrend_renderer_prepare_reset();

   if (state.context_initialized)
      virgl_context_table_reset();

   if (state.resource_initialized)
      virgl_resource_table_reset();

   if (state.vkr_initialized)
      vkr_renderer_reset();

   if (state.vrend_initialized)
      vrend_renderer_reset();
}

int virgl_renderer_get_poll_fd(void)
{
   TRACE_FUNC();
   if (state.vrend_initialized)
      return vrend_renderer_get_poll_fd();

   return -1;
}

virgl_debug_callback_type virgl_set_debug_callback(virgl_debug_callback_type cb)
{
   return vrend_set_debug_callback(cb);
}

static int virgl_renderer_export_query(void *execute_args, uint32_t execute_size)
{
   struct virgl_resource *res;
   struct virgl_renderer_export_query *export_query = execute_args;
   if (execute_size != sizeof(struct virgl_renderer_export_query))
      return -EINVAL;

   if (export_query->hdr.size != sizeof(struct virgl_renderer_export_query))
      return -EINVAL;

   res = virgl_resource_lookup(export_query->in_resource_id);
   if (!res)
      return -EINVAL;


   if (res->pipe_resource) {
      return vrend_renderer_export_query(res->pipe_resource, export_query);
   } else if (!export_query->in_export_fds) {
      /* Untyped resources are expected to be exported with
       * virgl_renderer_resource_export_blob instead and have no type
       * information.  But when this is called to query (in_export_fds is
       * false) an untyped resource, we should return sane values.
       */
      export_query->out_num_fds = 1;
      export_query->out_fourcc = 0;
      export_query->out_fds[0] = -1;
      export_query->out_strides[0] = 0;
      export_query->out_offsets[0] = 0;
      export_query->out_modifier = DRM_FORMAT_MOD_INVALID;
      return 0;
   } else {
      return -EINVAL;
   }
}

static int virgl_renderer_supported_structures(void *execute_args, uint32_t execute_size)
{
   struct virgl_renderer_supported_structures *supported_structures = execute_args;
   if (execute_size != sizeof(struct virgl_renderer_supported_structures))
      return -EINVAL;

   if (supported_structures->hdr.size != sizeof(struct virgl_renderer_supported_structures))
      return -EINVAL;

   if (supported_structures->in_stype_version == 0) {
      supported_structures->out_supported_structures_mask =
         VIRGL_RENDERER_STRUCTURE_TYPE_EXPORT_QUERY |
         VIRGL_RENDERER_STRUCTURE_TYPE_SUPPORTED_STRUCTURES;
   } else {
      supported_structures->out_supported_structures_mask = 0;
   }

   return 0;
}

int virgl_renderer_execute(void *execute_args, uint32_t execute_size)
{
   TRACE_FUNC();
   struct virgl_renderer_hdr *hdr = execute_args;
   if (hdr->stype_version != 0)
      return -EINVAL;

   switch (hdr->stype) {
      case VIRGL_RENDERER_STRUCTURE_TYPE_SUPPORTED_STRUCTURES:
         return virgl_renderer_supported_structures(execute_args, execute_size);
      case VIRGL_RENDERER_STRUCTURE_TYPE_EXPORT_QUERY:
         return virgl_renderer_export_query(execute_args, execute_size);
      default:
         return -EINVAL;
   }
}

int virgl_renderer_resource_create_blob(const struct virgl_renderer_resource_create_blob_args *args)
{
   TRACE_FUNC();
   struct virgl_resource *res;
   struct virgl_context *ctx;
   struct virgl_context_blob blob;
   bool has_host_storage;
   bool has_guest_storage;
   int ret;

   switch (args->blob_mem) {
   case VIRGL_RENDERER_BLOB_MEM_GUEST:
      has_host_storage = false;
      has_guest_storage = true;
      break;
   case VIRGL_RENDERER_BLOB_MEM_HOST3D:
      has_host_storage = true;
      has_guest_storage = false;
      break;
   case VIRGL_RENDERER_BLOB_MEM_HOST3D_GUEST:
      has_host_storage = true;
      has_guest_storage = true;
      break;
   default:
      return -EINVAL;
   }

   /* user resource id must be greater than 0 */
   if (args->res_handle == 0)
      return -EINVAL;

   if (args->size == 0)
      return -EINVAL;
   if (has_guest_storage) {
      const size_t iov_size = vrend_get_iovec_size(args->iovecs, args->num_iovs);
      if (iov_size < args->size)
         return -EINVAL;
   } else {
      if (args->num_iovs)
         return -EINVAL;
   }

   if (!has_host_storage) {
      res = virgl_resource_create_from_iov(args->res_handle,
                                           args->iovecs,
                                           args->num_iovs);
      if (!res)
         return -ENOMEM;

      res->map_info = VIRGL_RENDERER_MAP_CACHE_CACHED;
      return 0;
   }

   ctx = virgl_context_lookup(args->ctx_id);
   if (!ctx)
      return -EINVAL;

   ret = ctx->get_blob(ctx, args->blob_id, args->blob_flags, &blob);
   if (ret)
      return ret;

   if (blob.type != VIRGL_RESOURCE_FD_INVALID) {
      res = virgl_resource_create_from_fd(args->res_handle,
                                          blob.type,
                                          blob.u.fd,
                                          args->iovecs,
                                          args->num_iovs);
      if (!res) {
         close(blob.u.fd);
         return -ENOMEM;
      }
   } else {
      res = virgl_resource_create_from_pipe(args->res_handle,
                                            blob.u.pipe_resource,
                                            args->iovecs,
                                            args->num_iovs);
      if (!res) {
         vrend_renderer_resource_destroy((struct vrend_resource *)blob.u.pipe_resource);
         return -ENOMEM;
      }
   }

   res->map_info = blob.map_info;

   if (ctx->get_blob_done)
      ctx->get_blob_done(ctx, args->res_handle, &blob);

   return 0;
}

int virgl_renderer_resource_map(uint32_t res_handle, void **map, uint64_t *out_size)
{
   TRACE_FUNC();
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!res || !res->pipe_resource)
      return -EINVAL;

   return vrend_renderer_resource_map(res->pipe_resource, map, out_size);
}

int virgl_renderer_resource_unmap(uint32_t res_handle)
{
   TRACE_FUNC();
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!res || !res->pipe_resource)
      return -EINVAL;

   return vrend_renderer_resource_unmap(res->pipe_resource);
}

int virgl_renderer_resource_get_map_info(uint32_t res_handle, uint32_t *map_info)
{
   TRACE_FUNC();
   struct virgl_resource *res = virgl_resource_lookup(res_handle);
   if (!res)
      return -EINVAL;

   if ((res->map_info & VIRGL_RENDERER_MAP_CACHE_MASK) ==
       VIRGL_RENDERER_MAP_CACHE_NONE)
      return -EINVAL;

   *map_info = res->map_info;
   return 0;
}

int
virgl_renderer_resource_export_blob(uint32_t res_id, uint32_t *fd_type, int *fd)
{
   struct virgl_resource *res = virgl_resource_lookup(res_id);
   if (!res)
      return EINVAL;

   switch (virgl_resource_export_fd(res, fd)) {
   case VIRGL_RESOURCE_FD_DMABUF:
      *fd_type = VIRGL_RENDERER_BLOB_FD_TYPE_DMABUF;
      break;
   case VIRGL_RESOURCE_FD_OPAQUE:
      *fd_type = VIRGL_RENDERER_BLOB_FD_TYPE_OPAQUE;
      break;
   default:
      return EINVAL;
   }

   return 0;
}

int
virgl_renderer_export_fence(uint32_t client_fence_id, int *fd)
{
   TRACE_FUNC();
   /* XXX sync_merge? */
   return -1;
   return vrend_renderer_export_ctx0_fence(client_fence_id, fd);
}
