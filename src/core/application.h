#pragma once

#include "layer.h"
#include "window.h"
#include "gui_layer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "gl/all.hpp"

#include <deque>
#include <memory>

#ifndef NDEBUG
void debug_message_callback(const gl::debug_log& log);
#endif

class Application {
 public:
  Application(std::string_view name, uint32_t width, uint32_t height);

  void run();

  void push_layer(LayerStack::LayerPtr&& layer) {
    layers_.push(std::move(layer));
  }

 private:
  Window window_;
  LayerStack layers_;
  std::unique_ptr<GuiLayer> gui_layer_{};
};
