#pragma once
#include "Algae/Resource/ResourceBuffer.hpp"
#include <string>

namespace alg {

namespace Resource {

void init();
void shutdown();

ResourceBuffer load_from_os_bundle(std::string name, std::string extens);
ResourceBuffer load_from_os_bundle(std::string name, std::string extens,
                                   std::string subdir);

} // namespace Resource
} // namespace alg
