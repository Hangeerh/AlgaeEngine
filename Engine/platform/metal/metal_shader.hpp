#pragma once

#include "renderer/shader.hpp"

class MetalShader : public Shader {
  friend class MetalRenderer;

private:
  void *vertex_function;
  void *fragment_function;

public:
  MetalShader();
  ~MetalShader();
};
