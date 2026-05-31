#pragma once

#include "renderer/renderer.hpp"
#include <GLFW/glfw3.h>
#include <string>

namespace alg {

struct CoreWindowSpec {
  int height = 600;
  int width = 800;
};

struct CoreApplicationSpec {
  std::string name = std::string("Application");
  CoreWindowSpec windowSpec;
};

class CoreApplication {
public:
  CoreApplication(CoreApplicationSpec appSpec);
  ~CoreApplication();

  void run();

private:
  CoreApplicationSpec appSpec;

  GLFWwindow *glfwWindow;
  Renderer *renderer;
};
} // namespace alg
