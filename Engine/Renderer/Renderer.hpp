#pragma once
#include "Renderer/RenderAPI.hpp"
#include <cstdint>
#include <memory>
#include <string>

namespace alg {

namespace Renderer {

void init(void *native_window);
void shutdown();

void begin_scene();
void bind_pipeline(std::shared_ptr<Pipeline> pipeline);
void submit(std::shared_ptr<VertexArray> vertex_array,
            std::shared_ptr<Buffer> uniforms);
void end_scene();

void on_window_resize(uint32_t width, uint32_t height);

std::shared_ptr<Buffer> make_buffer(int size);
std::shared_ptr<Buffer> make_buffer(const void *bytes, int size);

std::shared_ptr<VertexArray>
make_vertex_array(const float *vertices, uint32_t vertex_size,
                  const uint32_t *indices, uint32_t index_count);

std::shared_ptr<Shader> make_shader(std::string function_name);

std::shared_ptr<Pipeline> make_pipeline(PipelineDescriptor pipeline_desc);

RenderAPI::Platform get_platform();

} // namespace Renderer
} // namespace alg
