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

enum EventCategory {
  None = 0,
  Application = 1 << 0,
  Input = 1 << 1,
  Keyboard = 1 << 2,
  Mouse = 1 << 3
};

class Event {
public:
  virtual ~Event() = default;

  bool handled = false;

  virtual EventType get_event_type() const = 0;
  virtual std::string get_name() const = 0;

  virtual int get_category_flags() const = 0;

  bool is_in_category(EventCategory category) {
    return get_category_flags() & category;
  }
};

#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType get_static_type() { return EventType::type; }               \
  EventType get_event_type() const override { return get_static_type(); }      \
  std::string get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                         \
  virtual int get_category_flags() const override { return category; }

#define BIND_EVENT_FN(fn)                                                      \
  [this](auto &&...args) -> decltype(auto) {                                   \
    return this->fn(std::forward<decltype(args)>(args)...);                    \
  }

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
