#pragma once
#include "Renderer/Buffers.hpp"
#include "Renderer/RenderPipeline.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"
#include <cstdint>
#include <memory>
#include <string>

namespace alg {

class RenderAPI {
public:
  enum class Platform {
    NONE,
    METAL,
  };

  static const Platform platform = Platform::METAL;

  RenderAPI(void *native_window);
  RenderAPI() = default;
  virtual ~RenderAPI() = 0;

  virtual void begin_scene() = 0;
  virtual void bind_pipeline(std::shared_ptr<Pipeline> pipeline) = 0;
  virtual void submit(std::shared_ptr<VertexArray> vertex_array,
                      std::shared_ptr<Buffer> uniforms) = 0;
  virtual void end_scene() = 0;

  virtual void on_window_resize(uint32_t width, uint32_t height) = 0;

  virtual std::shared_ptr<Buffer> make_buffer(int size) = 0;
  virtual std::shared_ptr<Buffer> make_buffer(const void *bytes, int size) = 0;

  virtual std::shared_ptr<VertexArray>
  make_vertex_array(const float *vertices, uint32_t vertex_size,
                    const uint32_t *indices, uint32_t index_count) = 0;

  virtual std::shared_ptr<Shader> make_shader(std::string function_name) = 0;

  virtual std::shared_ptr<Pipeline>
  make_pipeline(PipelineDescriptor pipeline_desc) = 0;

  static RenderAPI *create(void *native_window);
  static Platform get_platform() { return platform; }
};
} // namespace alg
