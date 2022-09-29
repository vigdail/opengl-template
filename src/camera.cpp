#include "../include/vgl/camera.h"

Camera::Camera(const glm::mat4& projection) : projection_{projection} {
}

void Camera::set_position(const glm::vec3& position) {
  position_ = position;
  is_dirty_ = true;
}

void Camera::set_rotation(const glm::quat& rotation) {
  rotation_ = glm::normalize(rotation);
  is_dirty_ = true;
}

const glm::mat4& Camera::get_view() {
  if (is_dirty_) {
    const glm::mat4 t = glm::translate(glm::mat4(1.0f), -position_);
    const glm::mat4 r = glm::mat4_cast(rotation_);

    view_ = r * t;
    is_dirty_ = false;
  }
  return view_;
}

const glm::mat4& Camera::get_projection() const {
  return projection_;
}
const glm::vec3& Camera::get_position() const {
  return position_;
}
const glm::quat& Camera::get_rotation() const {
  return rotation_;
}

void FpsCameraController::update(float delta_time) {
  if (!is_first_ && input.mouse_down) {
    const auto mouse_delta = input.mouse_position - prev_mouse_position_;

    const float mouse_speed = 0.1f * delta_time;
    const glm::quat delta_quat = glm::quat(
        glm::vec3(mouse_speed * mouse_delta.y, mouse_speed * mouse_delta.x, 0.0f));
    camera_->set_rotation(delta_quat * camera_->get_rotation());
    set_up_vector(glm::vec3(0.0f, 1.0f, 0.0f));
  }
  is_first_ = false;

  prev_mouse_position_ = input.mouse_position;

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
    move_speed_ -= move_speed_ * std::min((1.0f / damping_) * delta_time, 1.0f);
  } else {
    move_speed_ += accel * acceleration_ * delta_time;
    if (glm::length(move_speed_) > max_speed_) {
      move_speed_ = glm::normalize(move_speed_) * max_speed_;
    }
  }

  camera_->set_position(camera_->get_position() + move_speed_ * delta_time);
}

void FpsCameraController::set_up_vector(const glm::vec3 up) {
  const glm::mat4 view = camera_->get_view();
  const glm::vec3 dir = -glm::vec3(view[0][2], view[1][2], view[2][2]);
  const auto& position = camera_->get_position();
  camera_->set_rotation(glm::lookAt(position, position + dir, up));
}
