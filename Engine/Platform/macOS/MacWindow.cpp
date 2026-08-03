#include "Platform/macOS/MacWindow.hpp"
#include "Algae/Core/Window.hpp"
#include "Algae/Event/ApplicationEvent.hpp"
#include "Algae/Event/KeyEvent.hpp"
#include "Algae/Event/MouseEvent.hpp"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace alg {

MacWindow::MacWindow(WindowSpec win_spec) {
  data.width = win_spec.width;
  data.height = win_spec.height;
  data.name = win_spec.name;

  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  native_handle = glfwCreateWindow(win_spec.width, win_spec.height,
                                   win_spec.name.c_str(), nullptr, nullptr);

  glfwSetWindowUserPointer(native_handle, &data);

  glfwSetWindowSizeCallback(
      native_handle, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent e(width, height);
        data.event_callback(e);
      });

  glfwSetWindowCloseCallback(native_handle, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    WindowCloseEvent e;
    data.event_callback(e);
  });

  glfwSetKeyCallback(native_handle, [](GLFWwindow *window, int key,
                                       int scancode, int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    switch (action) {
    case GLFW_PRESS: {
      KeyPressedEvent e(key);
      data.event_callback(e);
      break;
    }
    case GLFW_REPEAT: {
      KeyPressedEvent e(key, true);
      data.event_callback(e);
      break;
    }
    case GLFW_RELEASE: {
      KeyReleasedEvent e(key);
      data.event_callback(e);
      break;
    }
    }
  });

  glfwSetMouseButtonCallback(
      native_handle, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent e(button);
          data.event_callback(e);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent e(button);
          data.event_callback(e);
          break;
        }
        }
      });

  glfwSetScrollCallback(
      native_handle, [](GLFWwindow *window, double offset_x, double offset_y) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseScrolledEvent e((float)offset_x, (float)offset_y);
        data.event_callback(e);
      });

  glfwSetCursorPosCallback(
      native_handle, [](GLFWwindow *window, double x, double y) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseScrolledEvent e((float)x, (float)y);
        data.event_callback(e);
      });

  glfwMakeContextCurrent(native_handle);
}

MacWindow::~MacWindow() {
  if (native_handle) {
    glfwDestroyWindow(native_handle);
  }
  glfwTerminate();
}

void *MacWindow::get_native_window() const {
  return glfwGetCocoaWindow(native_handle);
}

bool MacWindow::should_close() const {
  return glfwWindowShouldClose(native_handle);
}

void MacWindow::set_event_callback_fn(EventCallbackFn fn) {
  data.event_callback = fn;
}

void MacWindow::on_update() { glfwPollEvents(); }

uint32_t MacWindow::get_height() const { return data.height; }

uint32_t MacWindow::get_width() const { return data.width; }
} // namespace alg
