#pragma once
#include <cstddef>

namespace alg {

class ResourceBuffer {
public:
  ResourceBuffer() = default;
  ResourceBuffer(char *bytes, size_t size);

  size_t size() const;
  char get(size_t byte_index) const;

private:
  char *bufstart;
  size_t bufsize;
};

} // namespace alg
