#pragma once

#include "Renderer/Shader.hpp"

namespace alg {

class MetalShader : public Shader {
private:
  void *function;

public:
  MetalShader();
  ~MetalShader();

  void set_internal_function(void *f);
  void *get_internal_function();
};

} // namespace alg
