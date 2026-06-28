#include "Core/Application.hpp"
#include "Renderer/Renderer.hpp"
#include <cassert>

namespace alg {

Application::Application(AppSpec app_spec) : app_spec(app_spec) {}

Application::~Application() { Renderer::shutdown(); }

void Application::set_window(void *window) {
  assert(window != nullptr);
  native_window = window;
  Renderer::init(native_window);
}

void Application::push_layer(Layer *layer) { layer_stack.push_layer(layer); }

void Application::push_overlay(Layer *overlay) {
  layer_stack.push_overlay(overlay);
}

} // namespace alg
