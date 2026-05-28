#pragma once

#include <cstddef>

class Buffer {
public:
  Buffer() = default;

  Buffer(void *bytes, int size);
  virtual ~Buffer() = default;

  virtual int get_size() const = 0;
};
