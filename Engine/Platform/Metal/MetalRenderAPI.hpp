#pragma once
#include "Algae/Renderer/RenderAPI.hpp"
#include <cstdint>
#include <memory>

namespace alg {

// Wrapper around swift renderer backend
class MetalRenderAPI : public RenderAPI {
private:
  void *internal_ptr;
  uint32_t drawable_height;
  uint32_t drawable_width;

public:
  MetalRenderAPI(std::shared_ptr<Window> window);
  ~MetalRenderAPI();
  void begin_scene() override;
  void bind_pipeline(std::shared_ptr<Pipeline> pipeline) override;
  void bind_depth_stencil_state(
      std::shared_ptr<DepthStencilState> depth_stencil) override;
  void submit(std::shared_ptr<VertexArray> vertex_array,
              std::shared_ptr<Buffer> uniforms) override;
  void end_scene() override;
  void on_window_resize(uint32_t width, uint32_t height) override;

  std::shared_ptr<Buffer> make_buffer(int size) override;
  std::shared_ptr<Buffer> make_buffer(const void *bytes, int size) override;

  std::shared_ptr<VertexArray> make_vertex_array(const float *vertices,
                                                 uint32_t vertex_size,
                                                 const uint32_t *indices,
                                                 uint32_t index_count) override;

  std::shared_ptr<Shader> make_shader(std::string function_name) override;

  std::shared_ptr<DepthStencilState>
  make_depth_stencil(DepthStencilDescriptor desc) override;

  std::shared_ptr<Pipeline>
  make_pipeline(PipelineDescriptor pipeline_desc) override;

  uint32_t get_drawable_height() const override;
  uint32_t get_drawable_width() const override;
};
} // namespace alg
