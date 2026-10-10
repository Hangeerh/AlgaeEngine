#pragma once
#include "Algae/Renderer/Texture.hpp"

namespace alg {

class MetalTexture : public Texture {
public:
  MetalTexture(void *mtl_texture);
  ~MetalTexture() override;

  void *get_ptr();

private:
  void *internal_ptr;
};

class MetalSampler : public Sampler {
public:
  MetalSampler(void *mtl_sampler);
  ~MetalSampler() override;

  void *get_ptr();

private:
  void *internal_ptr;
};
} // namespace alg
