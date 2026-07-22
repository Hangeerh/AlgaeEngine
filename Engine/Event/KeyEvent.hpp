#pragma once

#include "Core/KeyCode.hpp"
#include "Event/Event.hpp"

namespace alg {

class KeyEvent : public Event {
public:
  KeyCode get_key_code() const { return key_code; }

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

protected:
  KeyEvent(const KeyCode keycode) : key_code(keycode) {}

  KeyCode key_code;
};

class KeyPressedEvent : public KeyEvent {
public:
  EVENT_CLASS_TYPE(KeyPressed)

  KeyPressedEvent(const KeyCode keycode, bool repeat_press = false)
      : KeyEvent(keycode), is_repeated(repeat_press) {}

  bool is_repeat() { return is_repeated; }

private:
  bool is_repeated;
};

class KeyReleasedEvent : public KeyEvent {
public:
  EVENT_CLASS_TYPE(KeyReleased)

  KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}
};
} // namespace alg
