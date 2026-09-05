#pragma once
#include "Algae/Core/Window.hpp"
#include "Algae/Renderer/Buffers.hpp"
#include "Algae/Renderer/DepthStencil.hpp"
#include "Algae/Renderer/RenderPipeline.hpp"
#include "Algae/Renderer/Shader.hpp"
#include "Algae/Renderer/VertexArray.hpp"
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

  RenderAPI(std::shared_ptr<Window> window);
  RenderAPI() = default;
  virtual ~RenderAPI() = 0;

  virtual void begin_scene() = 0;
  virtual void bind_pipeline(std::shared_ptr<Pipeline> pipeline) = 0;
  virtual void bind_depth_stencil_state(
      std::shared_ptr<DepthStencilState> depth_stencil) = 0;
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

  virtual std::shared_ptr<DepthStencilState>
  make_depth_stencil(DepthStencilDescriptor desc) = 0;

  virtual std::shared_ptr<Pipeline>
  make_pipeline(PipelineDescriptor pipeline_desc) = 0;

  virtual uint32_t get_drawable_height() const = 0;
  virtual uint32_t get_drawable_width() const = 0;

  static RenderAPI *create(std::shared_ptr<Window> window);
  static Platform get_platform() { return platform; }
};
} // namespace alg
