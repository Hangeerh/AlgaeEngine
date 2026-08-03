#pragma once

#include "Algae/Core/Layer.hpp"
#include <vector>

namespace alg {

class LayerStack {
public:
  LayerStack() = default;
  ~LayerStack();

  void push_layer(Layer *layer);
  void push_overlay(Layer *overlay);
  void pop_layer(Layer *layer);
  void pop_overlay(Layer *overlay);

  std::vector<Layer *>::iterator begin() { return layers.begin(); }
  std::vector<Layer *>::iterator end() { return layers.end(); }
  std::vector<Layer *>::reverse_iterator rbegin() { return layers.rbegin(); }
  std::vector<Layer *>::reverse_iterator rend() { return layers.rend(); }

  std::vector<Layer *>::const_iterator begin() const {
    return layers.begin();
  }
  std::vector<Layer *>::const_iterator end() const { return layers.end(); }
  std::vector<Layer *>::const_reverse_iterator rbegin() const {
    return layers.rbegin();
  }
  std::vector<Layer *>::const_reverse_iterator rend() const {
    return layers.rend();
  }

private:
  std::vector<Layer *> layers;
  unsigned int layer_insert_index = 0;
};
} // namespace alg
