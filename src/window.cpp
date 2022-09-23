#include "window.h"

#include <GLFW/glfw3.h>

#include <stdexcept>

KeyAction key_action(int glfw_action) {
  switch (glfw_action) {
    case GLFW_PRESS:
      return KeyAction::Pressed;
    case GLFW_RELEASE:
      return KeyAction::Released;
    case GLFW_REPEAT:
      return KeyAction::Repeat;
  }
  throw std::runtime_error("Unknown Key Action: " + std::to_string(glfw_action));
}

Window::Window(std::string_view title, uint32_t width, uint32_t height) {
  if (glfwInit() == GLFW_FALSE) {
    throw std::runtime_error("Unable to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
  if (!window_) {
    const char* buff[1024];
    glfwGetError(buff);
    glfwTerminate();
    throw std::runtime_error(std::string("Unable to create window: ") + *buff);
  }
  glfwMakeContextCurrent(window_);

  glfwSetWindowUserPointer(window_, this);
  glfwSetMouseButtonCallback(window_, [](GLFWwindow* w, int button, int action, int mods) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
    KeyAction button_action = key_action(action);
    self->handler_(MouseButtonEvent{button, button_action});
  });

  glfwSetKeyCallback(window_, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
    KeyAction button_action = key_action(action);
    self->handler_(KeyEvent{key, button_action});
  });

  glfwSetCursorPosCallback(window_, [](GLFWwindow* w, double x, double y) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
    self->handler_(MouseMoveEvent{static_cast<float>(x), static_cast<float>(y)});
  });
}

void Window::swap() {
  glfwSwapBuffers(window_);
}

void Window::pool_events() {
  glfwPollEvents();
}

void Window::set_event_handler(const EventHandler& handler) {
  handler_ = handler;
}

Window::~Window() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

bool Window::should_close() {
  return glfwWindowShouldClose(window_);
}
void Window::close() {
  glfwSetWindowShouldClose(window_, GLFW_TRUE);
}
void Window::hide_cursor() {
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Window::show_cursor() {
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void Window::toggle_cursor() {
  int mode = glfwGetInputMode(window_, GLFW_CURSOR);
  if (mode == GLFW_CURSOR_DISABLED) {
    show_cursor();
  } else {
    hide_cursor();
  }
}
