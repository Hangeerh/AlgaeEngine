#include "platform/metal/metal_vertex_array.hpp"
#include <sys/types.h>

MetalVertexArray::~MetalVertexArray() = default;

void MetalVertexArray::set_vertex_buffer(
    const std::shared_ptr<Buffer> vertex_buffer) {
  this->vertex_buffer = vertex_buffer;
}

void MetalVertexArray::set_index_buffer(
    const std::shared_ptr<Buffer> index_buffer, uint32_t index_count) {
  this->index_buffer = index_buffer;
  this->index_count = index_count;
}
