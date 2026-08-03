#include "Algae/Core/Window.hpp"
#include "Platform/macOS/MacWindow.hpp"

namespace alg {

Window::Window(WindowSpec win_spec) {};

std::shared_ptr<Window> Window::create(WindowSpec win_spec) {
#ifdef __APPLE__
  return std::make_shared<MacWindow>(win_spec);
#endif
  return nullptr;
}
} // namespace alg
