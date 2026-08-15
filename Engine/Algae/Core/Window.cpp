#include "Algae/Core/Window.hpp"
#include "Platform/OSX/OSXWindow.hpp"

namespace alg {

Window::Window(WindowSpec win_spec) {};

std::shared_ptr<Window> Window::create(WindowSpec win_spec) {
#ifdef __APPLE__
  return std::make_shared<OSXWindow>(win_spec);
#endif
  return nullptr;
}
} // namespace alg
