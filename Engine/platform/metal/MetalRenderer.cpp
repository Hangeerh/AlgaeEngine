#include "MetalRenderer.hpp"
#include "./c_api.hpp"
#include "platform/metal/metal_buffers.hpp"
#include "platform/metal/metal_render_pipeline.hpp"
#include "platform/metal/metal_shader.hpp"
#include "platform/metal/metal_vertex_array.hpp"
#include <cstdint>
#include <memory>
#include <string>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace alg {

MetalRenderer::MetalRenderer(GLFWwindow *glfw_window) {
  void *nswin_ptr = glfwGetCocoaWindow(glfw_window);
  internal_ptr = _renderer_init(nswin_ptr);
}

MetalRenderer::~MetalRenderer() { _renderer_deinit(internal_ptr); }

void MetalRenderer::begin_scene() { _renderer_begin_scene(internal_ptr); }

void MetalRenderer::bind_pipeline(std::shared_ptr<Pipeline> pipeline) {
  void *pipeline_ptr =
      ((MetalPipeline *)pipeline.get())->get_metal_pipeline_ptr();
  _renderer_bind_pipeline(internal_ptr, pipeline_ptr);
}

void MetalRenderer::submit(std::shared_ptr<VertexArray> vertex_array) {
  std::shared_ptr<MetalBuffer> vertex_buffer =
      std::static_pointer_cast<MetalBuffer>(vertex_array->get_vertex_buffer());
  std::shared_ptr<MetalBuffer> index_buffer =
      std::static_pointer_cast<MetalBuffer>(vertex_array->get_index_buffer());

  _renderer_submit(internal_ptr, vertex_buffer->get_metal_buffer_ptr(),
                   index_buffer->get_metal_buffer_ptr(),
                   vertex_array->get_index_count());
}

void MetalRenderer::end_scene() { _renderer_end_scene(internal_ptr); }

void MetalRenderer::on_window_resize(uint32_t width, uint32_t height) {
  _renderer_on_window_resize(internal_ptr, width, height);
}

std::shared_ptr<Buffer> MetalRenderer::make_buffer(int size) {
  void *buf_ptr = _renderer_make_buffer(internal_ptr, size);
  return std::make_shared<MetalBuffer>(buf_ptr, size);
}

std::shared_ptr<Buffer> MetalRenderer::make_buffer(const void *bytes,
                                                   int size) {
  void *buf_ptr = _renderer_make_buffer_bytes(internal_ptr, bytes, size);
  return std::make_shared<MetalBuffer>(buf_ptr, size);
}

std::shared_ptr<VertexArray>
MetalRenderer::make_vertex_array(const float *vertices, uint32_t vertex_size,
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

std::shared_ptr<Shader>
MetalRenderer::make_shader(std::string vertex_function,
                           std::string fragment_function) {
  void *fragment_shader =
      _renderer_make_shader(internal_ptr, fragment_function.c_str());
  void *vertex_shader =
      _renderer_make_shader(internal_ptr, vertex_function.c_str());

  auto shader = std::make_shared<MetalShader>();
  shader->fragment_function = fragment_shader;
  shader->vertex_function = vertex_shader;

  return shader;
}

std::shared_ptr<Pipeline>
MetalRenderer::make_pipeline(PipelineDescriptor pipeline_desc) {
  void *vertex_shader =
      ((MetalShader *)pipeline_desc.shader.get())->vertex_function;
  void *fragment_shader =
      ((MetalShader *)pipeline_desc.shader.get())->fragment_function;

  void *pipeline = _renderer_make_pipeline(
      internal_ptr, static_cast<uint32_t>(pipeline_desc.vertex_format),
      pipeline_desc.off_set, pipeline_desc.buffer_index, pipeline_desc.stride,
      vertex_shader, fragment_shader);

  return std::make_shared<MetalPipeline>(pipeline);
}
} // namespace alg
