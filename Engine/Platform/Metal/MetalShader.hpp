#pragma once

#include "Renderer/Shader.hpp"

namespace alg {

class MetalShader : public Shader {
  friend class MetalRenderAPI;

private:
  void *vertex_function;
  void *fragment_function;

public:
  MetalShader();
  ~MetalShader();
};

} // namespace alg
