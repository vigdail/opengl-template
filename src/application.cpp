#include "application.h"
void debug_message_callback(const gl::debug_log& log) {
  std::cerr << log.message << std::endl;
}

Application::Application(std::string_view name, uint32_t width, uint32_t height) : window_{name, width, height} {
  gl::initialize();

#ifndef NDEBUG
  gl::set_debug_output_enabled(true);
  gl::set_synchronous_debug_output_enabled(true);
  gl::set_debug_log_callback(debug_message_callback);
  gl::set_debug_log_filters(GL_DONT_CARE, GL_DONT_CARE, {},
                            GL_DEBUG_SEVERITY_NOTIFICATION, false);
#endif

  window_.hide_cursor();
  window_.set_event_handler([this](const WindowEvent& event) {
    auto key_handler = Handler<KeyEvent, WindowEvent>([&](const auto& event) {
      bool is_pressed = event.action == KeyAction::Pressed;
      if (event.key_code == GLFW_KEY_ESCAPE && is_pressed) {
        window_.close();
      }
    });
    key_handler(event);
    for (const auto& layer: layers_) {
      layer->on_event(event);
    }
  });
}

void Application::run() {
  double time_stamp = glfwGetTime();
  while (!window_.should_close()) {
    window_.swap();
    window_.pool_events();

    const double new_time_stamp = glfwGetTime();
    const auto delta_seconds = static_cast<float>(new_time_stamp - time_stamp);
    time_stamp = new_time_stamp;
    for (const auto& layer: layers_) {
      layer->on_update(delta_seconds);
    }
  }
}
