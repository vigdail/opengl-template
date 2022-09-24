#include "application.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "window.h"

#include <GLFW/glfw3.h>
#include <gl/all.hpp>
#include <gl/auxiliary/glm_uniforms.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <memory>

class FramesPerSecondCounter {
 public:
  explicit FramesPerSecondCounter(float avg_interval_secs) : avg_interval_secs_{avg_interval_secs} {
    assert(avg_interval_secs > 0.0f);
  }

  bool tick(float delta_seconds, bool frame_rendered = true) {
    if (frame_rendered) {
      num_frames_++;
    }

    accumulated_time_ += delta_seconds;
    if (accumulated_time_ < avg_interval_secs_) {
      return false;
    }

    current_fps_ = static_cast<float>(num_frames_ / accumulated_time_);
    num_frames_ = 0;
    accumulated_time_ = 0.0;
    return true;
  }

  inline float get_fps() const {
    return current_fps_;
  }

 private:
  const float avg_interval_secs_{0.5};
  uint32_t num_frames_{0};
  double accumulated_time_{0.0};
  float current_fps_{0.0f};
};

class ExampleLayer : public Layer {
 public:
  ExampleLayer(float camera_aspect_ratio) : camera_{glm::perspective(glm::radians(60.0f), camera_aspect_ratio, 0.01f, 1000.0f)},
                                            controller_{&camera_},
                                            shader_{load_shader("../assets/shaders/triangle.vert", "../assets/shaders/triangle.frag")},
                                            vao_{new gl::vertex_array},
                                            texture_{load_texture("../assets/textures/texture.png")} {
  }

  void on_attach() override {
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

  void on_update(float delta_seconds) override {
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

  void on_gui() override {
    float fps = fps_counter_.get_fps();
    ImGui::Begin("Example");
    if (fps > 0.0f) {
      ImGui::Text("FPS: %.0f", fps);
      ImGui::Text("Frame time: %.2f ms", 1000.0f / fps);
    }
    ImGui::End();
  }

  void on_event(const WindowEvent& event) override {
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

 private:
  Camera camera_;
  FpsCameraController controller_;
  std::shared_ptr<gl::program> shader_;
  std::shared_ptr<gl::vertex_array> vao_;
  std::shared_ptr<gl::texture_2d> texture_;
  FramesPerSecondCounter fps_counter_{0.5f};
};

int main() {
  Application app("OpenGL", 1280, 720);
  app.push_layer(std::make_unique<ExampleLayer>(1280.0f / 720.0f));
  app.run();
  return 0;
}
