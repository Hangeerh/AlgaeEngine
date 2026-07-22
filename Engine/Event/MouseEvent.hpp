#pragma once

#include "Core/MouseCode.hpp"
#include "Event/Event.hpp"

namespace alg {

class MouseMovedEvent : public Event {
public:
  EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  EVENT_CLASS_TYPE(MouseMoved)

  MouseMovedEvent(const float x, const float y) : mouse_x(x), mouse_y(y) {}

  float get_x() { return mouse_x; }
  float get_y() { return mouse_y; }

private:
  float mouse_x;
  float mouse_y;
};

class MouseScrolledEvent : public Event {
public:
  EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  EVENT_CLASS_TYPE(MouseScrolled)

  MouseScrolledEvent(const float x, const float y) : offset_x(x), offset_y(y) {}

  float get_x_offset() { return offset_x; }
  float get_y_offset() { return offset_y; }

private:
  float offset_x;
  float offset_y;
};

class MouseButtonEvent : public Event {
public:
  EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse |
                       EventCategoryInput)

  MouseCode get_mouse_button() const { return mouse_button; }

protected:
  MouseButtonEvent(const MouseCode button) : mouse_button(button) {}

  MouseCode mouse_button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
  EVENT_CLASS_TYPE(MousePressed)

  MouseButtonPressedEvent(const MouseCode button) : MouseButtonEvent(button) {}
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  EVENT_CLASS_TYPE(MouseReleased)

  MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}
};
} // namespace alg
