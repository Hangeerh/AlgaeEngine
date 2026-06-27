#include "platform/metal/MetalBuffers.hpp"
#include "./c_api.hpp"

namespace alg {

MetalBuffer::MetalBuffer(void *bytes, int size) {
  internal_ptr = bytes;
  this->size = size;
}

MetalBuffer::~MetalBuffer() { _release_metal_buffer(internal_ptr); }

void *MetalBuffer::get_metal_buffer_ptr() { return internal_ptr; }

int MetalBuffer::get_size() const { return _mtl_buffer_get_size(internal_ptr); }
} // namespace alg
