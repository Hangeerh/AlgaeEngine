#include "Platform/OSX/OSXIOAPI.hpp"
#include <cstddef>

extern "C" {
void _load_from_osx_bundle(const char *name, const char *extension,
                           const char *subdirectory, char **out_bytes,
                           size_t *out_size);
}

namespace alg {

IOBuffer OSXIOAPI::load_from_os_bundle(std::string name,
                                                   std::string extens) const {
  char *bytes = nullptr;
  size_t size = 0;
  _load_from_osx_bundle(name.c_str(), extens.c_str(), nullptr, &bytes, &size);
  return IOBuffer(bytes, size);
}

IOBuffer OSXIOAPI::load_from_os_bundle(std::string name,
                                                   std::string extens,
                                                   std::string subdir) const {
  char *bytes = nullptr;
  size_t size = 0;
  _load_from_osx_bundle(name.c_str(), extens.c_str(), subdir.c_str(), &bytes,
                        &size);
  return IOBuffer(bytes, size);
}

} // namespace alg
