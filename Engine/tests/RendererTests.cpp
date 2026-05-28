#include "platform/metal/MetalRenderer.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>

void error_callback(int error, const char *description) {
  std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

int main() {
  std::cout << "[Test] Starting MetalRenderer initialization tests..."
            << std::endl;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    std::cerr << "[Test] Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Create a hidden window
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Test Window", nullptr, nullptr);
  if (!window) {
    std::cerr << "[Test] Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  std::cout << "[Test] Window created successfully." << std::endl;

  Renderer *renderer = nullptr;
  try {
    std::cout << "[Test] Initializing MetalRenderer..." << std::endl;
    renderer = new MetalRenderer(window);
    std::cout << "[Test] MetalRenderer initialized successfully." << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "[Test] Exception during MetalRenderer initialization: "
              << e.what() << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  if (!renderer) {
    std::cerr << "[Test] Renderer pointer is null!" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  std::cout << "[Test] Running update loop for 5 frames..." << std::endl;
  for (int i = 0; i < 5; ++i) {
    renderer->update();
    glfwPollEvents();
  }
  std::cout << "[Test] Update loop completed without crashing." << std::endl;

  std::cout << "[Test] Cleaning up..." << std::endl;
  delete renderer;
  glfwDestroyWindow(window);
  glfwTerminate();

  std::cout << "[Test] All tests passed!" << std::endl;
  return 0;
}
