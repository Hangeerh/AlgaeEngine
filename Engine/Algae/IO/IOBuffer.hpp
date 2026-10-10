#pragma once
#include <cstddef>

namespace alg {

class IOBuffer {
public:
  IOBuffer() = default;
  ~IOBuffer() = default;
  IOBuffer(char *bytes, size_t size);

  IOBuffer slice(size_t start, size_t size);

  char *get_ptr() const;
  size_t size() const;
  char get(size_t byte_index) const;

private:
  char *bufstart = nullptr;
  size_t bufsize = 0;
};

} // namespace alg
