#include "Renderer.hpp"
#include "Platform/Metal/MetalRenderer.hpp"

namespace alg {

Renderer::Renderer(void *native_window) {}
Renderer::~Renderer() {}

Renderer *Renderer::create(void *native_window) {
  switch (platform) {
  case Renderer::Platform::METAL:
    return new MetalRenderer(native_window);
  case Renderer::Platform::NONE:
    return nullptr;
  }
}
} // namespace alg
