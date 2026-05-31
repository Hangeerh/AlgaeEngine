#include "platform/metal/metal_shader.hpp"
#include "./c_api.hpp"

namespace alg {

MetalShader::MetalShader() {
  vertex_function = nullptr;
  fragment_function = nullptr;
}

MetalShader::~MetalShader() {
  _free_metal_shader(vertex_function);
  _free_metal_shader(fragment_function);
}

} // namespace alg
