#pragma once
#include "Algae/Resource/ResourceBuffer.hpp"
#include <string>

namespace alg {

class ResourceAPI {
public:
  enum class Platform {
    NONE = 0,
    OSX,
  };

  ResourceAPI() = default;
  ~ResourceAPI() = default;

  virtual ResourceBuffer load_from_os_bundle(std::string name,
                                             std::string extens) const = 0;
  virtual ResourceBuffer load_from_os_bundle(std::string name,
                                             std::string extens,
                                             std::string subdir) const = 0;

  static const Platform platform = Platform::OSX;
  static ResourceAPI *create();
};

} // namespace alg
