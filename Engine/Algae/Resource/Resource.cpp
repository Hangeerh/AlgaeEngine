#include "Algae/Resource/Resource.hpp"
#include "Algae/Resource/ResourceAPI.hpp"
#include <memory>

namespace alg {
namespace Resource {

static std::unique_ptr<ResourceAPI> s_api;

void init() { s_api.reset(ResourceAPI::create()); }

void shutdown() { s_api.reset(); }

ResourceBuffer load_from_os_bundle(std::string name, std::string extens) {
  return s_api->load_from_os_bundle(name, extens);
}

ResourceBuffer load_from_os_bundle(std::string name, std::string extens,
                                   std::string subdir) {
  return s_api->load_from_os_bundle(name, extens, subdir);
}

} // namespace Resource
} // namespace alg
