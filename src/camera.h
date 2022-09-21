#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera {
 public:
  explicit Camera(const glm::mat4& projection);
  const glm::mat4& get_view();
  const glm::mat4& get_projection() const;
  void set_position(const glm::vec3& position);
  void set_rotation(const glm::quat& rotation);

 private:
  glm::quat rotation_{glm::quat(glm::vec3(0.0f, 0.0f, 1.0f))};
  glm::vec3 position_{};
  glm::mat4 view_{};
  glm::mat4 projection_;
  bool is_dirty_{true};
};
