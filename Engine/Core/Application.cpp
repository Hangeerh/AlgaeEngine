#include "Core/Application.hpp"
#include "Renderer/Renderer.hpp"
#include "Window/Window.hpp"
#include <cassert>

namespace alg {

Application::Application(AppSpec app_spec) : app_spec(app_spec) {}

Application::~Application() { Renderer::shutdown(); }

void Application::set_window(Window &window) {
  native_window = window.get_native_window();
  assert(native_window != nullptr);
  Renderer::init(native_window);
}

void Application::push_layer(Layer *layer) { layer_stack.push_layer(layer); }

void Application::push_overlay(Layer *overlay) {
  layer_stack.push_overlay(overlay);
}

void Application::run() {
  Window window(app_spec.name, app_spec.window_spec.width,
                app_spec.window_spec.height);

  set_window(window);

  while (!window.should_close()) {
    window.poll_events();
    window.swap_buffers();
  }
}

} // namespace alg
