#include "Platform/Metal/MetalTexture.hpp"
#include "Platform/Metal/c_api.hpp"

namespace alg {

MetalTexture::MetalTexture(void *mtl_texture) : internal_ptr(mtl_texture) {}

MetalTexture::~MetalTexture() { _release_metal_texture(internal_ptr); }

MetalSampler::MetalSampler(void *mtl_sampler) : internal_ptr(mtl_sampler) {}

MetalSampler::~MetalSampler() { _release_metal_sampler(internal_ptr); }
} // namespace alg
