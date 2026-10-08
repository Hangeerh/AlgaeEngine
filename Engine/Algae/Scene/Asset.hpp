#pragma once
#include "Algae/Renderer/RenderPipeline.hpp"
#include "Algae/Renderer/VertexArray.hpp"

namespace alg {

struct Mesh {
  std::shared_ptr<VertexArray> vertex_data;

  // For the vertex format
  std::map<int, VertexAttributeDescriptor> attributes;
  std::map<int, VertexBufferLayoutDescriptor> layouts;
};

} // namespace alg
