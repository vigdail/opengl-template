#include "camera.h"
#include "shader.h"
#include "texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/all.hpp>
#include <gl/auxiliary/glm_uniforms.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <memory>

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
constexpr const char* WINDOW_TITLE = "OpenGL Template";

#ifndef NDEBUG
void debug_message_callback(const gl::debug_log& log) {
  std::cerr << log.message << std::endl;
}
#endif

void key_callback(GLFWwindow* window, int key, int, int action, int) {
  auto* controller = static_cast<FPSCameraController*>(glfwGetWindowUserPointer(window));
  bool is_pressed = action != GLFW_RELEASE;
  if (key == GLFW_KEY_W) {
    controller->input.forward = is_pressed;
  }
  if (key == GLFW_KEY_S) {
    controller->input.backward = is_pressed;
  }
  if (key == GLFW_KEY_A) {
    controller->input.left = is_pressed;
  }
  if (key == GLFW_KEY_D) {
    controller->input.right = is_pressed;
  }
}

void cursor_pos_callback(GLFWwindow* window, double x, double y) {
  auto* controller = static_cast<FPSCameraController*>(glfwGetWindowUserPointer(window));
  controller->input.mouse_position = {static_cast<float>(x), static_cast<float>(y)};
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int /* mods */) {
  if (button != GLFW_MOUSE_BUTTON_1 || action != GLFW_PRESS) {
    return;
  }
  int mode = glfwGetInputMode(window, GLFW_CURSOR);
  if (mode == GLFW_CURSOR_DISABLED) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
}

int main() {
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Unable to initialize GLFW\n";
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
  if (!window) {
    const char* buff[1024];
    glfwGetError(buff);
    std::cerr << "Unable to create window: " << *buff;
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_pos_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  gl::initialize();

#ifndef NDEBUG
  gl::set_debug_output_enabled(true);
  gl::set_synchronous_debug_output_enabled(true);
  gl::set_debug_log_callback(debug_message_callback);
  gl::set_debug_log_filters(GL_DONT_CARE, GL_DONT_CARE, {},
                            GL_DEBUG_SEVERITY_NOTIFICATION, false);
#endif

  auto shader = load_shader("../assets/shaders/triangle.vert", "../assets/shaders/triangle.frag");
  auto texture = load_texture("../assets/textures/texture.png");
  std::shared_ptr<gl::vertex_array> vao(new gl::vertex_array);

  const glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float) WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 1000.0f);
  Camera camera(proj);
  const auto camera_position = glm::vec3(0.0f, 0.0f, 3.0f);
  const auto target_position = glm::vec3(0.0f, 0.0f, 0.0f);
  const auto dir = glm::normalize(camera_position - target_position);
  camera.set_position(camera_position);
  camera.set_rotation(glm::rotation(glm::vec3(0.0f, 0.0f, 1.0f), dir));

  FPSCameraController controller(&camera);

  glfwSetWindowUserPointer(window, &controller);

  vao->bind();
  texture->bind_unit(0);
  shader->use();
  shader->set_uniform(shader->uniform_location("u_texture"), 0);

  double time_stamp = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();

    const double new_time_stamp = glfwGetTime();
    const auto delta_seconds = static_cast<float>(new_time_stamp - time_stamp);
    time_stamp = new_time_stamp;

    controller.update(delta_seconds);
    const auto& view = camera.get_view();
    const glm::mat4 view_proj = proj * view;
    shader->set_uniform(shader->uniform_location("view_proj"), view_proj);

    gl::set_clear_color({0.0f, 0.0f, 0.0f, 1.0f});
    gl::clear(GL_COLOR_BUFFER_BIT);

    gl::draw_arrays(GL_TRIANGLES, 0, 6);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}
