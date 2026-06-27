#include "Renderer/Buffers.hpp"
#include <cassert>
#include <stdexcept>

namespace alg {

Buffer::Buffer(void *bytes, int size) {
  throw std::runtime_error("Cannot initialize abstract Buffer");
}

} // namespace alg
