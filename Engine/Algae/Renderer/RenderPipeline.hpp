#pragma once
#include "Algae/Renderer/Shader.hpp"
#include <memory>
#include <map>

namespace alg {

// Consistent with Metal graphics api
enum class VertexFormat {
  Invalid = 0,
  // 32 bit float
  Float = 28,
  Float2 = 29,
  Float3 = 30,
  Float4 = 31,
  // 32 bit signed int
  Int = 32,
  Int2 = 33,
  Int3 = 34,
  Int4 = 35,
  // 32 bit unsigned int
  UInt = 36,
  UInt2 = 37,
  UInt3 = 38,
  UInt4 = 39,
  // 16 bit float
  Half = 53,
  Half2 = 25,
  Half3 = 26,
  Half4 = 27,
  // 16 bit int
  Short = 50,
  Short2 = 16,
  Short3 = 17,
  Short4 = 18,
  // 16 bit unsigned int
  UShort = 49,
  UShort2 = 13,
  UShort3 = 14,
  UShort4 = 15,
};

enum class VertexStepFunction {
  Constant = 0,
  PerVertex,
  PerInstance,
  PerPatch,
  PerPatchControlPoint,
};

struct VertexAttributeDescriptor {
  VertexFormat format = VertexFormat::Invalid;
  int offset = 0;
  int buffer_index = 0;
};

struct VertexBufferLayoutDescriptor {
  VertexStepFunction step_function = VertexStepFunction::PerVertex;
  int step_rate = 1;
  int stride = 0;
};

class PipelineDescriptor {
public:
  PipelineDescriptor() = default;
  ~PipelineDescriptor() = default;

  // Vertex attribute descriptor array, prefilled by metal
  std::map<int, VertexAttributeDescriptor> attributes;

  // Buffer layout descriptor array, prefilled by metal
  std::map<int, VertexBufferLayoutDescriptor> layouts;

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
