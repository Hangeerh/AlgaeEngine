#include "Algae/IO/IOBuffer.hpp"
#include <cassert>

namespace alg {

IOBuffer::IOBuffer(char *bytes, size_t size) {
  assert(bytes != nullptr && "IOBuffer received empty buffer");
  assert(size > 0 && "IOBuffer cannot create empty buffer");
  bufstart = bytes;
  bufsize = size;
}

size_t IOBuffer::size() const { return bufsize; }

char IOBuffer::get(size_t byte_index) const {
  assert(byte_index < bufsize && "IOBuffer index out of range");

  return *(bufstart + byte_index);
}
} // namespace alg
