#pragma once

#include <string>

namespace alg {

enum class EventType {
  None = 0,
  WindowClose,
  WindowResize,
  AppUpdate,
  AppRender,
  KeyPressed,
  KeyReleased,
  MousePressed,
  MouseReleased,
  MouseMoved,
  MouseScrolled
};

class Event {
public:
  virtual ~Event() = default;

  bool handled = false;

  virtual EventType get_event_type() const = 0;
  virtual std::string get_name() const = 0;
};

#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType get_static_type() { return EventType::type; }               \
  EventType get_event_type() const override { return get_static_type(); }      \
  std::string get_name() const override { return #type; }

class EventDispatcher {
public:
  EventDispatcher(Event &event) : event(event) {}

  template <typename T, typename F> bool dispatch(const F &func) {
    if (event.get_event_type() == T::get_static_type() && !event.handled) {
      event.handled = func(static_cast<T &>(event));
      return true;
    }
    return false;
  }

private:
  Event &event;
};

} // namespace alg
