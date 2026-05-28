#pragma once

class vec4f {
public:
  float x;
  float y;
  float z;
  float w;

  ~vec4f() = default;

  vec4f(float f);
  vec4f(float x, float y, float z, float w);
};
