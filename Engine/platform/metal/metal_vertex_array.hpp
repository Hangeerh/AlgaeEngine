#pragma once

#include "platform/metal/MetalRenderer.hpp"
#include <cstdint>
#include <memory>

class MetalVertexArray : public VertexArray {
  friend class MetalRenderer;

public:
  ~MetalVertexArray();
  MetalVertexArray() = default;

  void set_vertex_buffer(const std::shared_ptr<Buffer> vertex_buffer) override;
  void set_index_buffer(const std::shared_ptr<Buffer> index_buffer,
                        uint32_t index_count) override;
};
