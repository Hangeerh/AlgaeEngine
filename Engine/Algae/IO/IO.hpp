#pragma once
#include "Algae/IO/IOBuffer.hpp"
#include <string>

namespace alg {

namespace IO {

void init();
void shutdown();

IOBuffer load_from_os_bundle(std::string name, std::string extens);
IOBuffer load_from_os_bundle(std::string name, std::string extens,
                                   std::string subdir);

} // namespace IO
} // namespace alg
