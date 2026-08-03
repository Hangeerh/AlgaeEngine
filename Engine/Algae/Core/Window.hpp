#pragma once

#include "Algae/Event/Event.hpp"
#include <cstdint>
#include <functional>
#include <string>

namespace alg {

struct WindowSpec {
  int height = 600;
  int width = 800;
  std::string name = std::string("Application");
};

using EventCallbackFn = std::function<void(Event &)>;

class Window {
public:
  Window() = default;
  Window(WindowSpec win_spec);

  virtual void *get_native_window() const = 0;
  virtual bool should_close() const = 0;
  virtual void set_event_callback_fn(EventCallbackFn fn) = 0;

  virtual void on_update() = 0;

  virtual uint32_t get_height() const = 0;
  virtual uint32_t get_width() const = 0;

  static std::shared_ptr<Window> create(WindowSpec win_spec);
};

} // namespace alg
