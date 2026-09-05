#pragma once

#include "Algae/Renderer/DepthStencil.hpp"

namespace alg {

class MetalDepthStencilState : public DepthStencilState {
private:
  void *internal_ptr;

public:
  explicit MetalDepthStencilState(void *state);
  ~MetalDepthStencilState() override;

  void *get_ptr();
};
} // namespace alg