#pragma once
#include "Renderer/Renderer.hpp"
#include <GLFW/glfw3.h>

namespace alg {

// Wrapper around swift renderer backend
class MetalRenderer : public Renderer {
private:
  void *internal_ptr;

public:
  MetalRenderer(GLFWwindow *glfw_window);
  ~MetalRenderer();
  void begin_scene() override;
  void bind_pipeline(std::shared_ptr<Pipeline> pipeline) override;
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

  std::shared_ptr<Shader> make_shader(std::string vertex_function,
                                      std::string fragment_function) override;

  std::shared_ptr<Pipeline>
  make_pipeline(PipelineDescriptor pipeline_desc) override;
};
} // namespace alg
