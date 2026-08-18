#include "Algae/IO/IO.hpp"
#include "Algae/IO/IOAPI.hpp"
#include <memory>

namespace alg {
namespace IO {

static std::unique_ptr<IOAPI> s_api;

void init() { s_api.reset(IOAPI::create()); }

void shutdown() { s_api.reset(); }

IOBuffer load_from_os_bundle(std::string name, std::string extens) {
  return s_api->load_from_os_bundle(name, extens);
}

IOBuffer load_from_os_bundle(std::string name, std::string extens,
                                   std::string subdir) {
  return s_api->load_from_os_bundle(name, extens, subdir);
}

} // namespace IO
} // namespace alg
