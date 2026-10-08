#pragma once
#include "Algae/IO/IOBuffer.hpp"
#include "Algae/Renderer/VertexArray.hpp"

namespace alg {

std::shared_ptr<VertexArray> deserialize_obj_file(IOBuffer buf);
}
