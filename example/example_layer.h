#pragma once

#include "../include/vgl/camera.h"
#include "../include/vgl/fps_counter.h"
#include "../include/vgl/layer.h"
#include "../include/vgl/shader.h"
#include "../include/vgl/texture.h"
#include "../include/vgl/window.h"

#include "GLFW/glfw3.h"
#include "gl/all.hpp"
#include "gl/auxiliary/glm_uniforms.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "imgui.h"

#include <memory>

class ExampleLayer : public Layer {
 public:
  ExampleLayer(float camera_aspect_ratio);

  void on_attach() override;

  void on_update(float delta_seconds) override;

  void on_gui() override;

  void on_event(const WindowEvent& event) override;

 private:
  Camera camera_;
  FpsCameraController controller_;
  std::shared_ptr<gl::program> shader_;
  std::shared_ptr<gl::vertex_array> vao_;
  std::shared_ptr<gl::texture_2d> texture_;
  FpsCounter fps_counter_{0.5f};
};
