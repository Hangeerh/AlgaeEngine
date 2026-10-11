#pragma once

#include "Algae/Core/Layer.hpp"
#include "Algae/Core/LayerStack.hpp"
#include "Algae/Core/Window.hpp"
#include "Algae/Event/ApplicationEvent.hpp"
#include "Algae/Event/Event.hpp"
#include <cstdint>

namespace alg {

struct AppSpec {
  WindowSpec window_spec;
  uint32_t ticks_per_second = 20;
};

class Application {
public:
  Application(AppSpec app_spec);
  virtual ~Application();

  void set_window(std::shared_ptr<Window> window);

  void on_event(Event &e);
  bool on_window_resize(WindowResizeEvent &e);
  bool on_window_close(WindowCloseEvent &e);

  void push_layer(Layer *layer);
  void push_overlay(Layer *layer);

  void run();

private:
  AppSpec app_spec;

  std::shared_ptr<Window> window;

  LayerStack layer_stack;

  uint32_t ticks_per_second;
  std::atomic<bool> running = true;
};
} // namespace alg
