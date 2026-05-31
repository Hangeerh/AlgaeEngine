#include "Engine.hpp"
#include "renderer/buffers.hpp"
#include "renderer/render_pipeline.hpp"
#include "renderer/renderer.hpp"
#include "renderer/vertex_array.hpp"
#include <GLFW/glfw3.h>
#include <memory>

namespace Engine {

CoreApplication::CoreApplication(CoreApplicationSpec appSpec) {
  this->appSpec = appSpec;
  const char *name = this->appSpec.name.c_str();
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindow =
      glfwCreateWindow(this->appSpec.windowSpec.width,
                       this->appSpec.windowSpec.height, name, NULL, NULL);
  glfwSetInputMode(glfwWindow, GLFW_CURSOR, 0);
  renderer = Renderer::create(glfwWindow);
}

CoreApplication::~CoreApplication() {
  delete renderer;
  glfwTerminate();
}

void CoreApplication::run() {
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // 0: Bottom Left
      0.5f,  -0.5f, 0.0f, // 1: Bottom Right
      0.0f,  0.5f,  0.0f  // 2: Top Center
  };

  unsigned int indices[] = {
      0, 1, 2 // Connects vertex 0 to 1 to 2
  };

  std::shared_ptr<VertexArray> vertex_array = renderer->make_vertex_array(
      (const float *)&vertices, sizeof(vertices), indices, 3);

  Shader *shader = renderer->make_shader("vertexMain", "fragmentMain");

  PipelineDescriptor pipeline_desc;
  pipeline_desc.vertex_format = VertexFormat::Float3;
  pipeline_desc.stride = sizeof(float) * 3;
  pipeline_desc.shader = std::shared_ptr<Shader>(shader);

  std::shared_ptr<Pipeline> pipeline = renderer->make_pipeline(pipeline_desc);

  while (!glfwWindowShouldClose(glfwWindow)) {
    glfwPollEvents();
    renderer->begin_scene();
    renderer->bind_pipeline(pipeline);
    renderer->submit(vertex_array);
    renderer->end_scene();
  }
}

}; // namespace Engine
