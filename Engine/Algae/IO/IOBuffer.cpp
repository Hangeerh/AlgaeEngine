#include "Algae/IO/IOBuffer.hpp"
#include <cassert>

namespace alg {

IOBuffer::IOBuffer(char *bytes, size_t size) : bufstart(bytes), bufsize(size) {}

IOBuffer IOBuffer::slice(size_t start, size_t size) {
  IOBuffer nbuf(bufstart + start, size);
  return nbuf;
}

char *IOBuffer::get_ptr() const { return bufstart; }

size_t IOBuffer::size() const { return bufsize; }

char IOBuffer::get(size_t byte_index) const {
  assert(byte_index < bufsize && "IOBuffer index out of range");

  return *(bufstart + byte_index);
}
} // namespace alg
