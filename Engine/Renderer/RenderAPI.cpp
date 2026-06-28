#include "Renderer/RenderAPI.hpp"
#include "Platform/Metal/MetalRenderAPI.hpp"

namespace alg {

RenderAPI::RenderAPI(void *native_window) {}
RenderAPI::~RenderAPI() {}

RenderAPI *RenderAPI::create(void *native_window) {
  switch (platform) {
  case RenderAPI::Platform::METAL:
    return new MetalRenderAPI(native_window);
  case RenderAPI::Platform::NONE:
    return nullptr;
  }
}
} // namespace alg
