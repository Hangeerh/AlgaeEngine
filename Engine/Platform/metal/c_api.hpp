#pragma once

#include <cstdint>
extern "C" {
//
// Renderer
//

// Initializes swift backend renderer from a CAMetalLayer ptr (void *)
void *_renderer_init(void *nswin_ptr);

// Destroys the swift renderer (void *)
void _renderer_deinit(void *swift_renderer_ptr);

void _renderer_begin_scene(void *swift_renderer_ptr);

void _renderer_bind_pipeline(void *swift_renderer_ptr, void *pipeline);

void _renderer_submit(void *swift_renderer_ptr, void *vertex_buffer,
                      void *index_buffer, uint32_t index_count,
                      void *uniform_buffer);

void _renderer_end_scene(void *swift_renderer_ptr);

void _renderer_on_window_resize(void *swift_renderer_ptr, uint32_t width,
                                uint32_t height);

void *_renderer_make_buffer(void *swift_renderer_ptr, int size);

void *_renderer_make_buffer_bytes(void *swift_renderer_ptr, const void *bytes,
                                  int size);

void *_renderer_make_shader(void *swift_renderer_ptr, const char *shader_name);

void *_renderer_make_pipeline(void *swift_renderer_ptr, uint32_t vertex_format,
                              int offset, int buffer_index, int stride,
                              void *vertex_shader, void *fragment_shader);

//
// Buffers
//

void _release_metal_buffer(void *buffer);

int _mtl_buffer_get_size(void *buffer);

//
// Shaders
//

void _free_metal_shader(void *shader);

void _release_metal_pipeline(void *pipeline);
}
