#pragma once

#include <cstdint>

namespace alg {

// Values match Metal's MTLStencilOperation enum.
enum class StencilOperation : uint32_t {
  Keep = 0,
  Zero = 1,
  Replace = 2,
  IncrementClamp = 3,
  DecrementClamp = 4,
  Invert = 5,
  IncrementWrap = 6,
  DecrementWrap = 7,
};

// Values match Metal's MTLCompareFunction enum.
enum class CompareFunction : uint32_t {
  Never = 0,
  Less = 1,
  Equal = 2,
  LessEqual = 3,
  Greater = 4,
  NotEqual = 5,
  GreaterEqual = 6,
  Always = 7,
};

class StencilDescriptor {
public:
  StencilDescriptor() = default;
  ~StencilDescriptor() = default;

  CompareFunction stencil_compare_function = CompareFunction::Always;
  StencilOperation stencil_failure_operation = StencilOperation::Keep;
  StencilOperation depth_failure_operation = StencilOperation::Keep;
  StencilOperation depth_stencil_pass_operation = StencilOperation::Keep;
  uint32_t read_mask = 0xFFFFFFFF;
  uint32_t write_mask = 0xFFFFFFFF;
};
} // namespace alg
