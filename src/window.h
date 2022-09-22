#pragma once

#include <string>
#include <functional>

enum class EventType {
  Key,
  MouseMove,
  MouseButton,
};

class Event {
 public:
  const EventType type;
};
enum class KeyAction {
  Pressed,
  Released,
};
class KeyEvent : public Event {
 public:
  KeyEvent(int key_code, KeyAction action) : Event{EventType::Key}, key_code{key_code}, action{action} {}

  const int key_code;
  const KeyAction action;
};

class MouseButtonEvent : public Event {
 public:
  MouseButtonEvent(int button, KeyAction action) : Event{EventType::MouseButton}, button{button}, action{action} {}
  const int button;
  const KeyAction action;
};

class MouseMoveEvent: public Event {
 public:
  MouseMoveEvent(float x, float y) : Event{EventType::MouseMove}, x{x}, y{y} {}
  const float x;
  const float y;
};

class GLFWwindow;

class Window final {
 public:
  using EventHandler = std::function<void(Event*)>;
  Window(std::string_view title, uint32_t key, uint32_t height);
  void swap();
  void pool_events();
  void set_event_handler(const EventHandler& handler);
  bool should_close();
  void close();
  void hide_cursor();
  void show_cursor();
  void toggle_cursor();
  virtual ~Window();

 private:
  GLFWwindow* window_{};
  EventHandler handler_{};
};
