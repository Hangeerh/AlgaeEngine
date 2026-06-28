#include "Renderer/VertexArray.hpp"

namespace alg {

std::shared_ptr<Buffer> VertexArray::get_vertex_buffer() {
  return vertex_buffer;
}

std::shared_ptr<Buffer> VertexArray::get_index_buffer() { return index_buffer; }

uint32_t VertexArray::get_index_count() const { return index_count; }

} // namespace alg
