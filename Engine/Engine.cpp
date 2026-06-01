#include "Engine.hpp"
#include "math/math.hpp"
#include "renderer/buffers.hpp"
#include "renderer/render_pipeline.hpp"
#include "renderer/renderer.hpp"
#include "renderer/vertex_array.hpp"
#include <GLFW/glfw3.h>
#include <memory>

namespace alg {

struct Uniforms {
  mat4 mvp_matrix;
};

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
      -0.5f, -0.5f, -0.5f, // 0
      0.5f,  -0.5f, -0.5f, // 1
      0.5f,  0.5f,  -0.5f, // 2
      -0.5f, 0.5f,  -0.5f, // 3
      -0.5f, -0.5f, 0.5f,  // 4
      0.5f,  -0.5f, 0.5f,  // 5
      0.5f,  0.5f,  0.5f,  // 6
      -0.5f, 0.5f,  0.5f   // 7
  };

  unsigned int indices[] = {
      4, 5, 6, 4, 6, 7, // Front
      1, 0, 3, 1, 3, 2, // Back
      3, 2, 6, 3, 6, 7, // Top
      0, 1, 5, 0, 5, 4, // Bottom
      1, 2, 6, 1, 6, 5, // Right
      0, 4, 7, 0, 7, 3  // Left
  };

  std::shared_ptr<VertexArray> vertex_array = renderer->make_vertex_array(
      (const float *)&vertices, sizeof(vertices), indices, 36);

  std::shared_ptr<Shader> shader =
      renderer->make_shader("vertexMain", "fragmentMain");

  PipelineDescriptor pipeline_desc;
  pipeline_desc.vertex_format = VertexFormat::Float3;
  pipeline_desc.stride = sizeof(float) * 3;
  pipeline_desc.shader = shader;

  std::shared_ptr<Pipeline> pipeline = renderer->make_pipeline(pipeline_desc);

  renderer->bind_pipeline(pipeline);

  float width = static_cast<float>(this->appSpec.windowSpec.width);
  float height = static_cast<float>(this->appSpec.windowSpec.height);
  mat4 projection =
      mat4_perspective(3.14159f / 4.0f, width / height, 0.1f, 100.0f);
  mat4 view =
      mat4_look_at({0.0f, 0.0f, 3.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});

  while (!glfwWindowShouldClose(glfwWindow)) {
    glfwPollEvents();

    float time = static_cast<float>(glfwGetTime());

    mat4 model = mat4_multiply(mat4_rotate_y(time), mat4_rotate_x(time * 0.5f));
    mat4 mvp = mat4_multiply(mat4_multiply(projection, view), model);

    Uniforms uniforms;
    uniforms.mvp_matrix = mvp;

    std::shared_ptr<Buffer> uniform_buffer =
        renderer->make_buffer(&uniforms, sizeof(Uniforms));

    renderer->begin_scene();
    renderer->submit(vertex_array, uniform_buffer);
    renderer->end_scene();
  }
}

} // namespace alg
