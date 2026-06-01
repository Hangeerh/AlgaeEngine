#pragma once

namespace alg {

struct vec4f {
  float x;
  float y;
  float z;
  float w;

  ~vec4f() = default;

  vec4f(float f) {
    x = f;
    y = f;
    z = f;
    w = f;
  }

  vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

struct mat4x4f {
  vec4f columns[4];
};

} // namespace alg
