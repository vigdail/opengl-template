#pragma once

#include "core/camera.h"
#include "core/layer.h"
#include "core/shader.h"
#include "core/texture.h"
#include "core/window.h"
#include "util/fps_counter.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <gl/all.hpp>
#include <gl/auxiliary/glm_uniforms.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

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
