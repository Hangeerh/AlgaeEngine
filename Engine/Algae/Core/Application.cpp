#include "Algae/Core/Application.hpp"
#include "Algae/Core/Window.hpp"
#include "Algae/Event/ApplicationEvent.hpp"
#include "Algae/Event/Event.hpp"
#include "Algae/IO/IO.hpp"
#include "Algae/Renderer/Renderer.hpp"
#include <cassert>
#include <chrono>
#include <memory>
#include <thread>

namespace alg {

Application::Application(AppSpec app_spec) : app_spec(app_spec) {
  IO::init();

  ticks_per_second = app_spec.ticks_per_second;

  window = Window::create(app_spec.window_spec);
  window->set_event_callback_fn(BIND_EVENT_FN(Application::on_event));
  set_window(window);
}

Application::~Application() { Renderer::shutdown(); }

void Application::set_window(std::shared_ptr<Window> window) {
  Renderer::init(window);
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
  std::atomic<bool> simulation_is_running = true;

  std::thread physics_thread([this, &simulation_is_running]() {
    const auto mspt = std::chrono::milliseconds(1000 / ticks_per_second);
    const float dt = 1.0f / (float)ticks_per_second;

    auto next_tick_time = std::chrono::high_resolution_clock::now() + mspt;
    while (simulation_is_running && running) {
      for (Layer *layer : layer_stack) {
        layer->on_update(dt);
      }

      std::this_thread::sleep_until(next_tick_time);
      next_tick_time += mspt;
    }
  });

  while (!window->should_close()) {
    window->on_update();

    for (Layer *layer : layer_stack) {
      layer->on_render();
    }
  }

  simulation_is_running = false;
  if (physics_thread.joinable()) {
    physics_thread.join();
  }
}

} // namespace alg
