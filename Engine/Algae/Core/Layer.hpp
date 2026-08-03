#pragma once

#include "Algae/Event/Event.hpp"
#include <string>

namespace alg {

class Layer {
public:
  Layer(const std::string &name = "Layer") : debug_name(name) {}
  virtual ~Layer() = default;

  virtual void on_attach();
  virtual void on_detach();
  virtual void on_update(float dt);
  virtual void on_render();
  virtual void on_event(Event &e);

  const std::string &get_name() { return debug_name; }

protected:
  std::string debug_name;
};
} // namespace alg
