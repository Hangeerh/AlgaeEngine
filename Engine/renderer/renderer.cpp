#include "renderer.hpp"
#include "platform/metal/MetalRenderer.hpp"

Renderer::Renderer(GLFWwindow *glfw_window) {}
Renderer::~Renderer() {}

Renderer *Renderer::create(GLFWwindow *glfw_window) {
  switch (platform) {
  case Renderer::Platform::METAL:
    return new MetalRenderer(glfw_window);
  case Renderer::Platform::NONE:
    return nullptr;
  }
}
