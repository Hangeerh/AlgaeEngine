#pragma once
#include "Algae/IO/IOBuffer.hpp"
#include <string>

namespace alg {

class IOAPI {
public:
  enum class Platform {
    NONE = 0,
    OSX,
  };

  IOAPI() = default;
  ~IOAPI() = default;

  virtual IOBuffer load_from_os_bundle(std::string name,
                                             std::string extens) const = 0;
  virtual IOBuffer load_from_os_bundle(std::string name,
                                             std::string extens,
                                             std::string subdir) const = 0;

  static const Platform platform = Platform::OSX;
  static IOAPI *create();
};

} // namespace alg
