#include "Algae/Renderer/RenderAPI.hpp"
#include "Platform/Metal/MetalRenderAPI.hpp"
#include <memory>

namespace alg {

RenderAPI::RenderAPI(std::shared_ptr<Window> window) {}
RenderAPI::~RenderAPI() {}

RenderAPI *RenderAPI::create(std::shared_ptr<Window> window) {
  switch (platform) {
  case RenderAPI::Platform::METAL:
    return new MetalRenderAPI(window);
  case RenderAPI::Platform::NONE:
    return nullptr;
  }
}
} // namespace alg
