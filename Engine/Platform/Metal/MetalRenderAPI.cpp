#include "MetalRenderAPI.hpp"
#include "./c_api.hpp"
#include "Platform/Metal/MetalBuffers.hpp"
#include "Platform/Metal/MetalRenderPipeline.hpp"
#include "Platform/Metal/MetalShader.hpp"
#include "Platform/Metal/MetalVertexArray.hpp"
#include <cstdint>
#include <memory>
#include <string>

namespace alg {

MetalRenderAPI::MetalRenderAPI(std::shared_ptr<Window> window) {
  drawable_height = window->get_height();
  drawable_width = window->get_width();

  void *native_window = window->get_native_window();
  internal_ptr = _renderer_init(native_window);
}

MetalRenderAPI::~MetalRenderAPI() { _renderer_deinit(internal_ptr); }

void MetalRenderAPI::begin_scene() { _renderer_begin_scene(internal_ptr); }

void MetalRenderAPI::bind_pipeline(std::shared_ptr<Pipeline> pipeline) {
  void *pipeline_ptr =
      ((MetalPipeline *)pipeline.get())->get_metal_pipeline_ptr();
  _renderer_bind_pipeline(internal_ptr, pipeline_ptr);
}

void MetalRenderAPI::submit(std::shared_ptr<VertexArray> vertex_array,
                            std::shared_ptr<Buffer> uniforms) {
  std::shared_ptr<MetalBuffer> vertex_buffer =
      std::static_pointer_cast<MetalBuffer>(vertex_array->get_vertex_buffer());
  std::shared_ptr<MetalBuffer> index_buffer =
      std::static_pointer_cast<MetalBuffer>(vertex_array->get_index_buffer());
  std::shared_ptr<MetalBuffer> uniform_buffer =
      std::static_pointer_cast<MetalBuffer>(uniforms);

  _renderer_submit(internal_ptr, vertex_buffer->get_metal_buffer_ptr(),
                   index_buffer->get_metal_buffer_ptr(),
                   vertex_array->get_index_count(),
                   uniform_buffer->get_metal_buffer_ptr());
}

void MetalRenderAPI::end_scene() { _renderer_end_scene(internal_ptr); }

void MetalRenderAPI::on_window_resize(uint32_t width, uint32_t height) {
  drawable_height = height;
  drawable_width = width;
  _renderer_on_window_resize(internal_ptr, width, height);
}

std::shared_ptr<Buffer> MetalRenderAPI::make_buffer(int size) {
  void *buf_ptr = _renderer_make_buffer(internal_ptr, size);
  return std::make_shared<MetalBuffer>(buf_ptr, size);
}

std::shared_ptr<Buffer> MetalRenderAPI::make_buffer(const void *bytes,
                                                    int size) {
  void *buf_ptr = _renderer_make_buffer_bytes(internal_ptr, bytes, size);
  return std::make_shared<MetalBuffer>(buf_ptr, size);
}

std::shared_ptr<VertexArray>
MetalRenderAPI::make_vertex_array(const float *vertices, uint32_t vertex_size,
                                  const uint32_t *indices,
                                  uint32_t index_count) {
  std::shared_ptr<Buffer> vertex_buffer = make_buffer(vertices, vertex_size);
  std::shared_ptr<Buffer> index_buffer =
      make_buffer(indices, index_count * sizeof(uint32_t));

  std::shared_ptr<VertexArray> va = std::make_shared<MetalVertexArray>();

  va->set_vertex_buffer(vertex_buffer);
  va->set_index_buffer(index_buffer, index_count);

  return std::static_pointer_cast<VertexArray>(va);
}

std::shared_ptr<Shader> MetalRenderAPI::make_shader(std::string function_name) {
  void *shader_ptr = _renderer_make_shader(internal_ptr, function_name.c_str());

  auto shader = std::make_shared<MetalShader>();
  shader->set_internal_function(shader_ptr);

  return shader;
}

std::shared_ptr<Pipeline>
MetalRenderAPI::make_pipeline(PipelineDescriptor pipeline_desc) {
  void *vertex_shader = ((MetalShader *)pipeline_desc.vertex_shader.get())
                            ->get_internal_function();
  void *fragment_shader = ((MetalShader *)pipeline_desc.fragment_shader.get())
                              ->get_internal_function();

  void *pipeline = _renderer_make_pipeline(
      internal_ptr, static_cast<uint32_t>(pipeline_desc.vertex_format),
      pipeline_desc.off_set, pipeline_desc.buffer_index, pipeline_desc.stride,
      vertex_shader, fragment_shader);

  return std::make_shared<MetalPipeline>(pipeline);
}

uint32_t MetalRenderAPI::get_drawable_height() const { return drawable_height; }

uint32_t MetalRenderAPI::get_drawable_width() const { return drawable_width; }
} // namespace alg
