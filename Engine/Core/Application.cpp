#include "Core/Application.hpp"
#include "Core/Window.hpp"
#include "Event/ApplicationEvent.hpp"
#include "Event/Event.hpp"
#include "Renderer/Renderer.hpp"
#include <cassert>
#include <memory>

namespace alg {

Application::Application(AppSpec app_spec) : app_spec(app_spec) {
  window = Window::create(app_spec.window_spec);

  window->set_event_callback_fn(BIND_EVENT_FN(Application::on_event));
  set_window(window);
}

Application::~Application() { Renderer::shutdown(); }

void Application::set_window(std::shared_ptr<Window> window) {
  native_window = window->get_native_window();
  assert(native_window != nullptr);
  Renderer::init(native_window);
}

void Application::on_event(Event &e) {
  EventDispatcher dispatcher(e);

  dispatcher.dispatch<WindowCloseEvent>(
      BIND_EVENT_FN(Application::on_window_close));
  dispatcher.dispatch<WindowResizeEvent>(
      BIND_EVENT_FN(Application::on_window_resize));

  for (auto it = layer_stack.rbegin(); it != layer_stack.rend(); ++it) {
    if (e.handled)
      break;

    (*it)->on_event(e);
  }
}

bool Application::on_window_resize(WindowResizeEvent &e) {
  Renderer::on_window_resize(e.width, e.height);
  return false;
}

bool Application::on_window_close(WindowCloseEvent &e) {
  running = false;
  return true;
}

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
