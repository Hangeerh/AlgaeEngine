#include "Algae/Renderer/Renderer.hpp"
#include "Algae/Core/Window.hpp"
#include "Algae/Renderer/RenderAPI.hpp"
#include <cstdint>

namespace alg {

namespace Renderer {

static std::unique_ptr<RenderAPI> s_api;

void init(std::shared_ptr<Window> window) {
  s_api.reset(RenderAPI::create(window));
}

void shutdown() { s_api.reset(); }

void begin_scene() { s_api->begin_scene(); }

void bind_pipeline(std::shared_ptr<Pipeline> pipeline) {
  s_api->bind_pipeline(pipeline);
}

void bind_depth_stencil_state(
    std::shared_ptr<DepthStencilState> depth_stencil) {
  s_api->bind_depth_stencil_state(depth_stencil);
}

void submit(std::shared_ptr<VertexArray> vertex_array,
            std::shared_ptr<Buffer> uniforms) {
  s_api->submit(vertex_array, uniforms);
}

void end_scene() { s_api->end_scene(); }

void on_window_resize(uint32_t width, uint32_t height) {
  s_api->on_window_resize(width, height);
}

std::shared_ptr<Buffer> make_buffer(int size) {
  return s_api->make_buffer(size);
}

std::shared_ptr<Buffer> make_buffer(const void *bytes, int size) {
  return s_api->make_buffer(bytes, size);
}

std::shared_ptr<VertexArray> make_vertex_array(const float *vertices,
                                               uint32_t vertex_size,
                                               const uint32_t *indices,
                                               uint32_t index_count) {
  return s_api->make_vertex_array(vertices, vertex_size, indices, index_count);
}

std::shared_ptr<Shader> make_shader(std::string function_name) {
  return s_api->make_shader(function_name);
}

std::shared_ptr<DepthStencilState>
make_depth_stencil_state(DepthStencilDescriptor desc) {
  return s_api->make_depth_stencil(desc);
}

std::shared_ptr<Pipeline> make_pipeline(PipelineDescriptor pipeline_desc) {
  return s_api->make_pipeline(pipeline_desc);
}

uint32_t get_drawable_height() { return s_api->get_drawable_height(); }

uint32_t get_drawable_width() { return s_api->get_drawable_width(); }

RenderAPI::Platform get_platform() { return RenderAPI::get_platform(); }

} // namespace Renderer
} // namespace alg
