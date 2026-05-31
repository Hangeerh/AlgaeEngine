#include "platform/metal/metal_render_pipeline.hpp"
#include "./c_api.hpp"

MetalPipeline::MetalPipeline(void *pipeline) { internal_ptr = pipeline; }

MetalPipeline::~MetalPipeline() { _release_metal_pipeline(internal_ptr); }

void *MetalPipeline::get_metal_pipeline_ptr() { return internal_ptr; }
