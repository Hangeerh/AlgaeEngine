#pragma once

#include "Renderer/RenderPipeline.hpp"

namespace alg {

class MetalPipeline : public Pipeline {
private:
  void *internal_ptr;

public:
  MetalPipeline() = default;
  MetalPipeline(void *pipeline);
  ~MetalPipeline() override;

  void *get_metal_pipeline_ptr();
};
} // namespace alg
