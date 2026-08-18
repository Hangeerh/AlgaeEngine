#include "Algae/Resource/ResourceBuffer.hpp"
#include <cassert>

namespace alg {

ResourceBuffer::ResourceBuffer(char *bytes, size_t size) {
  assert(bytes != nullptr && "ResourceBuffer received empty buffer");
  assert(size > 0 && "ResourceBuffer cannot create empty buffer");
  bufstart = bytes;
  bufsize = size;
}

size_t ResourceBuffer::size() const { return bufsize; }

char ResourceBuffer::get(size_t byte_index) const {
  assert(byte_index < bufsize && "ResourceBuffer index out of range");

  return *(bufstart + byte_index);
}
} // namespace alg
