#include "camera.h"

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
