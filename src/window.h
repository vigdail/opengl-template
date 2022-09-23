#pragma once

#include <functional>
#include <string>
#include <variant>

enum class KeyAction {
  Pressed,
  Released,
  Repeat,
};

struct KeyEvent {
  const int key_code;
  const KeyAction action;
};

struct MouseButtonEvent {
  const int button;
  const KeyAction action;
};

struct MouseMoveEvent {
  const float x;
  const float y;
};

struct WindowResizeEvent {
  const uint32_t width;
  const uint32_t height;
};

using WindowEvent = std::variant<KeyEvent, MouseMoveEvent, MouseButtonEvent, WindowResizeEvent>;

// TODO: Proper names
template<typename T, typename E>
class Handler {
 public:
  Handler(std::function<void(const T&)> function) : function_{function} {}

  void operator()(const E& event) {
    std::visit([&](const auto& e) {
      using Event = std::decay_t<decltype(e)>;
      if constexpr (std::is_same<T, Event>()) {
        function_(e);
      }
    },
               event);
  }

 private:
  std::function<void(const T&)> function_;
};

class GLFWwindow;

class Window final {
 public:
  using EventHandler = std::function<void(const WindowEvent&)>;
  Window(std::string_view title, uint32_t width, uint32_t height);
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
