#include "Core/Application.hpp"
#include "Core/Window.hpp"
#include "Renderer/Renderer.hpp"
#include <cassert>
#include <memory>

namespace alg {

Application::Application(AppSpec app_spec) : app_spec(app_spec) {
  window = Window::create(app_spec.window_spec);

  window->set_event_callback_fn([this](Event &e) { on_event(e); });
  set_window(window);
}

Application::~Application() { Renderer::shutdown(); }

void Application::set_window(std::shared_ptr<Window> window) {
  native_window = window->get_native_window();
  assert(native_window != nullptr);
  Renderer::init(native_window);
}

void Application::on_event(Event &e) {}

void Application::push_layer(Layer *layer) { layer_stack.push_layer(layer); }

void Application::push_overlay(Layer *overlay) {
  layer_stack.push_overlay(overlay);
}

void Application::run() {
  while (!window->should_close()) {

    for (Layer *layer : layer_stack) {
      layer->on_render();
    }

    window->on_update();
  }
}

} // namespace alg
