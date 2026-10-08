#pragma once

#include "Algae/Renderer/PixelFormat.hpp"
#include <cstdint>

namespace alg {

class Texture {
public:
  Texture() = default;
  virtual ~Texture() = default;
};

class Sampler {
public:
  Sampler() = default;
  virtual ~Sampler() = default;
};

enum class TextureUsage : uint32_t {
  Unknown = 0,
  ShaderRead = 1 << 0,
  ShaderWrite = 1 << 1,
  RenderTarget = 1 << 2,
};

constexpr TextureUsage operator|(TextureUsage lhs, TextureUsage rhs) {
  return static_cast<TextureUsage>(static_cast<uint32_t>(lhs) |
                                   static_cast<uint32_t>(rhs));
}

struct TextureDescriptor {
  PixelFormat pixel_format = PixelFormat::Invalid;
  uint32_t width = 1;
  uint32_t height = 1;
  uint32_t mipmap_level_count = 1;
  TextureUsage usage = TextureUsage::Unknown;
};

enum class SamplerMinMagFilter : uint32_t {
  Nearest = 0,
  Linear = 1,
};

enum class SamplerMipFilter : uint32_t {
  NotMipmapped = 0,
  Nearest = 1,
  Linear = 2,
};

enum class SamplerAddressMode : uint32_t {
  ClampToEdge = 0,
  MirrorRepeat = 1,
  Repeat = 2,
};

struct SamplerDescriptor {
  SamplerMinMagFilter min_filter = SamplerMinMagFilter::Nearest;
  SamplerMinMagFilter mag_filter = SamplerMinMagFilter::Nearest;
  SamplerMipFilter mip_filter = SamplerMipFilter::NotMipmapped;
  SamplerAddressMode s_address_mode = SamplerAddressMode::ClampToEdge;
  SamplerAddressMode t_address_mode = SamplerAddressMode::ClampToEdge;
};
} // namespace alg
