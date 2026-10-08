#pragma once
#include "Algae/IO/IOBuffer.hpp"
#include "Algae/Scene/Asset.hpp"

namespace alg {

class ObjFileDeserializer {
public:
  ObjFileDeserializer() = delete;
  ObjFileDeserializer(IOBuffer buf);

  Mesh deserialize();

private:
  IOBuffer buffer;

  size_t current_index = 0;

  bool not_at_end();
  IOBuffer getline();
};
} // namespace alg
