#include "Algae/Scene/Asset.hpp"

namespace alg {

class ObjFileParser {
public:
  ObjFileParser() = default;
  ObjFileParser(IOBuffer &obj_file) : buffer(obj_file) {}

  char current_char() { return buffer.get(current_index); }

private:
  IOBuffer &buffer;
  size_t current_index = 0;
};

// Seems that since we need to know about the vertex format, ie if it has
// normals, or uv, we might need to create an abstraction for a renderable asset
// instead of just a vertex array.
std::shared_ptr<VertexArray> deserialize_obj_file(IOBuffer buf) {}
} // namespace alg
