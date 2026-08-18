#pragma once
#include "Algae/Resource/ResourceAPI.hpp"

namespace alg {

class OSXResourceAPI : public ResourceAPI {
public:
  OSXResourceAPI() = default;
  ~OSXResourceAPI() = default;

  ResourceBuffer load_from_os_bundle(std::string name,
                                     std::string extens) const override;
  ResourceBuffer load_from_os_bundle(std::string name, std::string extens,
                                     std::string subdir) const override;
};

} // namespace alg
