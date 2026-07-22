#pragma once

#include "Event/Event.hpp"

namespace alg {

class WindowResizeEvent : public Event {
public:
  EVENT_CLASS_TYPE(WindowResize)

  unsigned int width, height;

  WindowResizeEvent(unsigned int width, unsigned int height)
      : width(width), height(height) {}
};

class WindowCloseEvent : public Event {
public:
  EVENT_CLASS_TYPE(WindowClose);

  WindowCloseEvent() = default;
};

class AppRenderEvent : public Event {
public:
  EVENT_CLASS_TYPE(AppRender)

  AppRenderEvent() = default;
};

}; // namespace alg
