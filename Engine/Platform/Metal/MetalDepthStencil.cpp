#include "Platform/Metal/MetalDepthStencil.hpp"
#include "Platform/Metal/c_api.hpp"

namespace alg {

MetalDepthStencilState::MetalDepthStencilState(void *state)
    : internal_ptr(state) {}

MetalDepthStencilState::~MetalDepthStencilState() {
  _release_metal_depth_stencil_state(internal_ptr);
}

void *MetalDepthStencilState::get_ptr() { return internal_ptr; }
} // namespace alg