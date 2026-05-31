#pragma once

#include "renderer/render_pipeline.hpp"

class MetalPipeline : public Pipeline {
private:
  void *internal_ptr;

public:
  MetalPipeline() = default;
  MetalPipeline(void *pipeline);
  ~MetalPipeline() override;

  void *get_metal_pipeline_ptr();
};
