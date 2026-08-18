#include "Algae/IO/IOAPI.hpp"
#include "Platform/OSX/OSXIOAPI.hpp"

namespace alg {

IOAPI *IOAPI::create() {
  switch (platform) {
  case Platform::NONE:
    return nullptr;
  case Platform::OSX:
    return new OSXIOAPI();
  }
}
} // namespace alg
