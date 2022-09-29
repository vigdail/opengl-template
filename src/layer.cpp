#include "../include/vgl/layer.h"

void LayerStack::push(LayerStack::LayerPtr layer) {
  layer->on_attach();
  layers_.push_back(std::move(layer));
}
