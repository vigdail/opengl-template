#pragma once

#include "window.h"

#include <deque>
#include <memory>

class Layer {
 public:
  virtual void on_attach() {}
  virtual void on_update(float dt) {}
  virtual void on_event(const WindowEvent& event) {}
  virtual void on_gui() {}
};

class LayerStack {
 public:
  using LayerPtr = std::unique_ptr<Layer>;
  void push(LayerPtr layer);
  std::deque<LayerPtr>::iterator begin() {
    return layers_.begin();
  }
  std::deque<LayerPtr>::iterator end() {
    return layers_.end();
  }

 private:
  std::deque<LayerPtr> layers_{};
};
