#pragma once

#include "buffers.hpp"
#include <Security/cssmconfig.h>
#include <cstdint>
#include <memory>

class VertexArray {
protected:
  std::shared_ptr<Buffer> vertex_buffer;
  std::shared_ptr<Buffer> index_buffer;
  uint32_t index_count;

public:
  VertexArray() = default;
  virtual ~VertexArray() = default;

  virtual void
  set_vertex_buffer(const std::shared_ptr<Buffer> vertex_buffer) = 0;
  virtual void set_index_buffer(const std::shared_ptr<Buffer> index_buffer,
                                uint32_t index_count) = 0;

  std::shared_ptr<Buffer> get_vertex_buffer();
  std::shared_ptr<Buffer> get_index_buffer();

  uint32_t get_index_count() const;
};
