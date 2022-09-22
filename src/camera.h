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

class FpsCameraController {
 public:
  struct Input {
    bool forward;
    bool backward;
    bool left;
    bool right;
    glm::vec2 mouse_position;
  };
  explicit FpsCameraController(Camera* camera) : camera_{camera} {}
  void update(float delta_time);

 public:
  Input input{};

 private:
  void set_up_vector(const glm::vec3 up);

 private:
  Camera* camera_;
  glm::vec2 prev_mouse_position_{};
  glm::vec3 move_speed_{};
  bool is_first_{true};
  float damping_{0.2f};
  float acceleration_{100.0f};
  float max_speed_{5.0f};
};