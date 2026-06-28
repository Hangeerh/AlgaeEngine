#include "Window/Window.hpp"

#include <GLFW/glfw3.h>

#ifdef __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>
#endif

namespace alg {

Window::Window(const std::string& title, uint32_t width, uint32_t height)
    : native_handle(nullptr)
{
    static bool glfw_initialized = false;
    if (!glfw_initialized) {
        glfwInit();
        glfw_initialized = true;
    }

    native_handle = glfwCreateWindow(
        static_cast<int>(width),
        static_cast<int>(height),
        title.c_str(),
        nullptr,
        nullptr
    );
}

Window::~Window() {
    if (native_handle) {
        glfwDestroyWindow(static_cast<GLFWwindow*>(native_handle));
    }
}

void* Window::get_native_window() const {
#ifdef __APPLE__
    return glfwGetCocoaWindow(static_cast<GLFWwindow*>(native_handle));
#else
    return native_handle;
#endif
}

bool Window::should_close() const {
    return glfwWindowShouldClose(static_cast<GLFWwindow*>(native_handle));
}

void Window::poll_events() const {
    glfwPollEvents();
}

void Window::swap_buffers() const {
    glfwSwapBuffers(static_cast<GLFWwindow*>(native_handle));
}

} // namespace alg
