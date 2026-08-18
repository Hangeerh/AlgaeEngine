#pragma once
#include "Algae/IO/IOAPI.hpp"

namespace alg {

class OSXIOAPI : public IOAPI {
public:
  OSXIOAPI() = default;
  ~OSXIOAPI() = default;

  IOBuffer load_from_os_bundle(std::string name,
                                     std::string extens) const override;
  IOBuffer load_from_os_bundle(std::string name, std::string extens,
                                     std::string subdir) const override;
};

} // namespace alg
