#pragma once

#include <cstddef>

namespace alg {

class Buffer {
public:
  Buffer() = default;

  Buffer(void *bytes, int size);
  virtual ~Buffer() = default;

  virtual int get_size() const = 0;
};
} // namespace alg
