#pragma once

#include "Core/Layer.hpp"
#include "Core/LayerStack.hpp"
#include "Event/Event.hpp"
#include "Window/Window.hpp"
#include <string>

namespace alg {

struct WindowSpec {
  int height = 600;
  int width = 800;
};

struct AppSpec {
  std::string name = std::string("Application");
  WindowSpec window_spec;
};

class Application {
public:
  Application(AppSpec app_spec);
  virtual ~Application();

  void set_window(Window *window);

  void on_event(Event &e);

  void push_layer(Layer *layer);
  void push_overlay(Layer *layer);

  void run();

private:
  AppSpec app_spec;

  Window *window;

  void *native_window = nullptr;
  LayerStack layer_stack;

  bool running = true;
};
} // namespace alg
