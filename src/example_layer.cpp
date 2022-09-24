#include "example_layer.h"
ExampleLayer::ExampleLayer(float camera_aspect_ratio) : camera_{glm::perspective(glm::radians(60.0f), camera_aspect_ratio, 0.01f, 1000.0f)},
                                                        controller_{&camera_},
                                                        shader_{load_shader("../assets/shaders/triangle.vert", "../assets/shaders/triangle.frag")},
                                                        vao_{new gl::vertex_array},
                                                        texture_{load_texture("../assets/textures/texture.png")} {
}

void ExampleLayer::on_attach() {
  const auto camera_position = glm::vec3(0.0f, 0.0f, 3.0f);
  const auto target_position = glm::vec3(0.0f, 0.0f, 0.0f);
  const auto dir = glm::normalize(camera_position - target_position);
  camera_.set_position(camera_position);
  camera_.set_rotation(glm::rotation(glm::vec3(0.0f, 0.0f, 1.0f), dir));

  vao_->bind();
  texture_->bind_unit(0);
  shader_->use();
  shader_->set_uniform(shader_->uniform_location("u_texture"), 0);
}

void ExampleLayer::on_update(float delta_seconds) {
  fps_counter_.tick(delta_seconds);
  controller_.update(delta_seconds);
  const auto& view = camera_.get_view();
  const auto& proj = camera_.get_projection();
  const glm::mat4 view_proj = proj * view;
  shader_->set_uniform(shader_->uniform_location("view_proj"), view_proj);

  gl::set_clear_color({0.0f, 0.0f, 0.0f, 1.0f});
  gl::clear(GL_COLOR_BUFFER_BIT);

  gl::draw_arrays(GL_TRIANGLES, 0, 6);
}

void ExampleLayer::on_gui() {
  float fps = fps_counter_.get_fps();
  ImGui::Begin("Example");
  if (fps > 0.0f) {
    ImGui::Text("FPS: %.0f", fps);
    ImGui::Text("Frame time: %.2f ms", 1000.0f / fps);
  }
  ImGui::End();
}

void ExampleLayer::on_event(const WindowEvent& event) {
  auto key_handler = Handler<KeyEvent, WindowEvent>([&](const auto& event) {
    bool is_pressed = event.action == KeyAction::Pressed || event.action == KeyAction::Repeat;
    if (event.key_code == GLFW_KEY_W) {
      controller_.input.forward = is_pressed;
    }
    if (event.key_code == GLFW_KEY_S) {
      controller_.input.backward = is_pressed;
    }
    if (event.key_code == GLFW_KEY_A) {
      controller_.input.left = is_pressed;
    }
    if (event.key_code == GLFW_KEY_D) {
      controller_.input.right = is_pressed;
    }
  });

  auto mouse_move_handler = Handler<MouseMoveEvent, WindowEvent>([&](const auto& event) {
    controller_.input.mouse_position = {event.x, event.y};
  });

  auto mouse_button_handler = Handler<MouseButtonEvent, WindowEvent>([&](const auto& event) {
    controller_.input.mouse_down = event.button == GLFW_MOUSE_BUTTON_1 && event.action != KeyAction::Released;
  });

  mouse_move_handler(event);
  key_handler(event);
  mouse_button_handler(event);
}
