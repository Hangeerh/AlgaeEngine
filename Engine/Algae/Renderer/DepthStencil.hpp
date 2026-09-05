#pragma once

#include "Algae/Renderer/Stencil.hpp"
#include <memory>

namespace alg {

class DepthStencilDescriptor {
public:
  DepthStencilDescriptor() = default;
  ~DepthStencilDescriptor() = default;

  CompareFunction depth_compare_function = CompareFunction::Always;
  bool depth_write_enabled = false;
  std::shared_ptr<StencilDescriptor> front_face_stencil = nullptr;
  std::shared_ptr<StencilDescriptor> back_face_stencil = nullptr;
};

class DepthStencilState {
public:
  DepthStencilState() = default;
  virtual ~DepthStencilState() = default;
};
} // namespace alg
