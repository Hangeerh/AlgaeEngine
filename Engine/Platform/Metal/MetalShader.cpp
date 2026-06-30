#include "Platform/Metal/MetalShader.hpp"
#include "./c_api.hpp"

namespace alg {

MetalShader::MetalShader() { function = nullptr; }

MetalShader::~MetalShader() { _free_metal_shader(function); }

void MetalShader::set_internal_function(void *f) { function = f; }
void *MetalShader::get_internal_function() { return function; }

} // namespace alg
