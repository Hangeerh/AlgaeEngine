#include "Algae/Resource/ResourceAPI.hpp"
#include "Platform/OSX/OSXResourceAPI.hpp"

namespace alg {

ResourceAPI *ResourceAPI::create() {
  switch (platform) {
  case Platform::NONE:
    return nullptr;
  case Platform::OSX:
    return new OSXResourceAPI();
  }
}
} // namespace alg
