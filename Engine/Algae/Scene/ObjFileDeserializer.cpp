#include "Algae/Scene/ObjFileDeserializer.hpp"
#include "Algae/IO/IOBuffer.hpp"
#include "Algae/Scene/Asset.hpp"

namespace alg {

ObjFileDeserializer::ObjFileDeserializer(IOBuffer buf) : buffer(buf) {}

bool ObjFileDeserializer::not_at_end() { return current_index < buffer.size(); }

IOBuffer ObjFileDeserializer::getline() {
  size_t start = current_index;

  while (not_at_end()) {
    char c = buffer.get(current_index++);
    if (c == '\n') {
      break;
    }
  }

  return buffer.slice(start, current_index - start);
}

Mesh ObjFileDeserializer::deserialize() {
  Mesh m;
  return m;
}

} // namespace alg
