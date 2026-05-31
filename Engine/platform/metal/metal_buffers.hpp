#pragma once

#include "renderer/buffers.hpp"

namespace alg {

class MetalBuffer : public Buffer {
private:
  void *internal_ptr;
  int size;

public:
  MetalBuffer() = default;

  MetalBuffer(void *bytes, int size);
  ~MetalBuffer() override;

  void *get_metal_buffer_ptr();

  int get_size() const override;
};
} // namespace alg
