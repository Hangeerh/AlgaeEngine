#pragma once
#include "renderer/buffers.hpp"
#include "renderer/render_pipeline.hpp"
#include "renderer/shader.hpp"
#include "renderer/vertex_array.hpp"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <memory>

class Renderer {
public:
  enum class Platform {
    NONE,
    METAL,
  };

  static const Platform platform = Platform::METAL;

  Renderer(GLFWwindow *glfw_window);
  Renderer() = default;
  virtual ~Renderer() = 0;

  virtual void begin_scene() = 0;
  virtual void bind_pipeline(std::shared_ptr<Pipeline> pipeline) = 0;
  // TODO: Add transforms
  virtual void submit(const Shader *shader,
                      std::shared_ptr<VertexArray> vertex_array) = 0;
  virtual void end_scene() = 0;

  virtual void on_window_resize(uint32_t width, uint32_t height) = 0;

  virtual std::shared_ptr<Buffer> make_buffer(int size) = 0;
  virtual std::shared_ptr<Buffer> make_buffer(const void *bytes, int size) = 0;

  virtual std::shared_ptr<VertexArray>
  make_vertex_array(const float *vertices, uint32_t vertex_size,
                    const uint32_t *indices, uint32_t index_count) = 0;

  virtual Shader *make_shader(std::string vertex_function,
                              std::string fragment_function) = 0;

  virtual std::shared_ptr<Pipeline>
  make_pipeline(PipelineDescriptor pipeline_desc) = 0;

  static Renderer *create(GLFWwindow *glfw_window);
  static Platform get_platform() { return platform; }
};
