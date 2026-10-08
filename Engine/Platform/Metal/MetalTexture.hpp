#pragma once
#include "Algae/Renderer/Texture.hpp"

namespace alg {

class MetalTexture : public Texture {
public:
  MetalTexture(void *mtl_texture);
  ~MetalTexture() override;

private:
  void *internal_ptr;
};

class MetalSampler : public Sampler {
public:
  MetalSampler(void *mtl_sampler);
  ~MetalSampler() override;

private:
  void *internal_ptr;
};
} // namespace alg
