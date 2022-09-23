#pragma once

#include <functional>
#include <string>
#include <variant>

enum class KeyAction {
  Pressed,
  Released,
};
class KeyEvent {
 public:
  KeyEvent(int key_code, KeyAction action) : key_code{key_code}, action{action} {}
  const int key_code;
  const KeyAction action;
};

class MouseButtonEvent {
 public:
  MouseButtonEvent(int button, KeyAction action) : button{button}, action{action} {}
  const int button;
  const KeyAction action;
};

class MouseMoveEvent {
 public:
  MouseMoveEvent(float x, float y) : x{x}, y{y} {}
  const float x;
  const float y;
};

using WindowEvent = std::variant<KeyEvent, MouseMoveEvent, MouseButtonEvent>;

class GLFWwindow;

class Window final {
 public:
  using EventHandler = std::function<void(const WindowEvent&)>;
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
