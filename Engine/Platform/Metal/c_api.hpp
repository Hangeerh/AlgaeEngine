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
void _renderer_bind_depth_stencil_state(void *swift_renderer_ptr,
                                        void *depth_stencil_state);

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

void *_renderer_make_pipeline(void *swift_renderer_ptr,
                              void *pipeline_descriptor);
void *_renderer_make_depth_stencil_state(void *swift_renderer_ptr,
                                         void *depth_stencil_descriptor);

//
// Pipeline building
//

void *_pipeline_desc_init();
void _pipeline_desc_set_vertex_function(void *pipeline, void *vertex_function);
void _pipeline_desc_set_fragment_function(void *pipeline,
                                          void *fragment_function);
void _pipeline_desc_set_vertex_desc(void *pipeline, void *vertex_desc);

void *_vertex_desc_init();
void _vertex_desc_set_attribute(void *desc, int index, int format, int offset,
                                int buffer_index);
void _vertex_desc_set_layout(void *desc, int index, int step_function,
                             int step_rate, int stride);

void _release_metal_pipeline_descriptor(void *pipeline_descriptor);
void _release_metal_vertex_descriptor(void *vertex_descriptor);

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

// Depth and stencil state building

void *_depth_stencil_desc_init();
void _depth_stencil_desc_set_depth_compare_function(void *desc,
                                                    int compare_function);
void _depth_stencil_desc_set_depth_write_enabled(void *desc, int enabled);
void _depth_stencil_desc_set_front_face_stencil(void *desc, void *stencil);
void _depth_stencil_desc_set_back_face_stencil(void *desc, void *stencil);

void *_stencil_desc_init();
void _stencil_desc_set_compare_function(void *desc, int compare_function);
void _stencil_desc_set_operations(void *desc, int stencil_failure,
                                  int depth_failure, int depth_stencil_pass);
void _stencil_desc_set_masks(void *desc, uint32_t read_mask,
                             uint32_t write_mask);

void _release_metal_depth_stencil_descriptor(void *descriptor);
void _release_metal_stencil_descriptor(void *descriptor);
void _release_metal_depth_stencil_state(void *state);
}
