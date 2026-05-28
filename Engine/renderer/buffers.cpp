#include "renderer/buffers.hpp"
#include <cassert>
#include <stdexcept>

Buffer::Buffer(void *bytes, int size) {
  throw std::runtime_error("Cannot initialize abstract Buffer");
}
