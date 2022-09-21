#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera {
 public:
  explicit Camera(const glm::mat4& projection);
  const glm::mat4& get_view();
  const glm::mat4& get_projection() const;
  void set_position(const glm::vec3& position);
  const glm::vec3& get_position() const;
  void set_rotation(const glm::quat& rotation);
  const glm::quat& get_rotation() const;

 private:
  glm::quat rotation_{glm::quat(glm::vec3(0.0f, 0.0f, 1.0f))};
  glm::vec3 position_{};
  glm::mat4 view_{};
  glm::mat4 projection_;
  bool is_dirty_{true};
};

class FPSCameraController {
 public:
  struct Input {
    bool forward;
    bool backward;
    bool left;
    bool right;
    glm::vec2 mouse_position;
  };
  explicit FPSCameraController(Camera* camera) : camera_{camera} {}
  void update(float delta_time) {
    // TODO: there should be class properties
    float damping = 0.2f;
    float acceleration = 100.0f;
    float max_speed = 5.0f;

    const auto mouse_delta = input.mouse_position - prev_mouse_position_;
    prev_mouse_position_ = input.mouse_position;

    const float mouse_speed = 10.0f;
    const glm::quat delta_quat = glm::quat(
        glm::vec3(mouse_speed * mouse_delta.y, mouse_speed * mouse_delta.x, 0.0f));
    camera_->set_rotation(glm::normalize(delta_quat * camera_->get_rotation()));

    const glm::mat4 v = glm::mat4_cast(camera_->get_rotation());
    const glm::vec3 forward = -glm::vec3(v[0][2], v[1][2], v[2][2]);
    const glm::vec3 right = glm::vec3(v[0][0], v[1][0], v[2][0]);
    const glm::vec3 up = glm::cross(right, forward);

    glm::vec3 accel{0.0f};
    if (input.forward) accel += forward;
    if (input.backward) accel -= forward;
    if (input.left) accel -= right;
    if (input.right) accel += right;

    if (accel == glm::vec3(0.0f)) {
      move_speed_ -= move_speed_ * std::min((1.0f / damping) * delta_time, 1.0f);
    } else {
      move_speed_ += accel * acceleration * delta_time;
      if (glm::length(move_speed_) > max_speed) {
        move_speed_ = glm::normalize(move_speed_) * max_speed;
      }
    }

    camera_->set_position(camera_->get_position() + move_speed_ * delta_time);
  }

 public:
  Input input{};

 private:
  Camera* camera_;
  glm::vec2 prev_mouse_position_{};
  glm::vec3 move_speed_{};
};