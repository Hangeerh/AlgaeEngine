#include "Platform/Metal/MetalRenderPipeline.hpp"
#include "./c_api.hpp"

namespace alg {

MetalPipeline::MetalPipeline(void *pipeline) { internal_ptr = pipeline; }

MetalPipeline::~MetalPipeline() { _release_metal_pipeline(internal_ptr); }

void *MetalPipeline::get_metal_pipeline_ptr() { return internal_ptr; }
} // namespace alg
