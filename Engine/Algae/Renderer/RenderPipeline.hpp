#pragma once
#include "Algae/Renderer/Shader.hpp"
#include <memory>

namespace alg {

enum class VertexFormat {
  // 32 bit float
  Float = 0,
  Float2,
  Float3,
  Float4,
  // 32 bit signed int
  Int,
  Int2,
  Int3,
  Int4,
  // 32 bit unsigned int
  UInt,
  UInt2,
  UInt3,
  UInt4,
  // 16 bit float
  Half,
  Half2,
  Half3,
  Half4,
  // 16 bit int
  Short,
  Short2,
  Short3,
  Short4,
  // 16 bit unsigned int
  UShort,
  UShort2,
  UShort3,
  UShort4,
};

class PipelineDescriptor {
public:
  PipelineDescriptor() = default;
  ~PipelineDescriptor() = default;

  // Vertex descriptor
  VertexFormat vertex_format = VertexFormat::Float3;
  int off_set = 0;
  int buffer_index = 0;
  int stride = 0;

  // Pipeline descriptor
  std::shared_ptr<Shader> vertex_shader = nullptr;
  std::shared_ptr<Shader> fragment_shader = nullptr;
};

class Pipeline {
public:
  Pipeline() = default;
  virtual ~Pipeline() = default;
};
} // namespace alg
