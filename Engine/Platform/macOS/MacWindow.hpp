#pragma once

#include "Core/Window.hpp"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

namespace alg {

class MacWindow : public Window {
public:
  MacWindow(WindowSpec win_spec);

  ~MacWindow();
  void *get_native_window() const override;
  bool should_close() const override;
  void set_event_callback_fn(EventCallbackFn fn) override;

  void on_update() override;

private:
  GLFWwindow *native_handle;

  struct WindowData {
    int height;
    int width;
    std::string name;

    EventCallbackFn event_callback;
  };

  WindowData data;
};
} // namespace alg
