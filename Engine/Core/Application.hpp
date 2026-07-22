#pragma once

#include "Core/Layer.hpp"
#include "Core/LayerStack.hpp"
#include "Event/Event.hpp"
#include "Core/Window.hpp"

namespace alg {

struct AppSpec {
  WindowSpec window_spec;
};

class Application {
public:
  Application(AppSpec app_spec);
  virtual ~Application();

  void set_window(std::shared_ptr<Window> window);

  void on_event(Event &e);

  void push_layer(Layer *layer);
  void push_overlay(Layer *layer);

  void run();

private:
  AppSpec app_spec;

  std::shared_ptr<Window> window;

  void *native_window = nullptr;
  LayerStack layer_stack;

  bool running = true;
};
} // namespace alg
