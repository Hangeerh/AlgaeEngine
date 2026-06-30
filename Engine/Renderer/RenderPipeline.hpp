#pragma once
#include "Renderer/Shader.hpp"
#include <memory>

namespace alg {

enum class VertexFormat {
  Float3 = 0,
};

class PipelineDescriptor {
public:
  PipelineDescriptor() = default;
  ~PipelineDescriptor() = default;

  VertexFormat vertex_format = VertexFormat::Float3;
  int off_set = 0;
  int buffer_index = 0;
  int stride = 0;

  std::shared_ptr<Shader> vertex_shader = nullptr;
  std::shared_ptr<Shader> fragment_shader = nullptr;
};

class Pipeline {
public:
  Pipeline() = default;
  virtual ~Pipeline() = default;
};
} // namespace alg
