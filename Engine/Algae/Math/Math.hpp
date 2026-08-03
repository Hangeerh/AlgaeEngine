#pragma once

#include <cmath>

namespace alg {

struct vec3 {
  float x, y, z;
};

inline vec3 vec3_sub(vec3 a, vec3 b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline vec3 vec3_add(vec3 a, vec3 b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline vec3 vec3_scale(vec3 v, float s) {
  return {v.x * s, v.y * s, v.z * s};
}

inline float vec3_dot(vec3 a, vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 vec3_cross(vec3 a, vec3 b) {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
          a.x * b.y - a.y * b.x};
}

inline float vec3_len(vec3 v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline vec3 vec3_normalize(vec3 v) {
  float len = vec3_len(v);
  if (len == 0.0f)
    return {0, 0, 0};
  return vec3_scale(v, 1.0f / len);
}

struct mat4 {
  float m[16];
};

inline mat4 mat4_identity() {
  return {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
}

inline mat4 mat4_multiply(const mat4 &a, const mat4 &b) {
  mat4 r = {};
  for (int col = 0; col < 4; ++col) {
    for (int row = 0; row < 4; ++row) {
      float sum = 0.0f;
      for (int k = 0; k < 4; ++k) {
        sum += a.m[k * 4 + row] * b.m[col * 4 + k];
      }
      r.m[col * 4 + row] = sum;
    }
  }
  return r;
}

inline mat4 mat4_translate(vec3 t) {
  mat4 r = mat4_identity();
  r.m[12] = t.x;
  r.m[13] = t.y;
  r.m[14] = t.z;
  return r;
}

inline mat4 mat4_rotate_y(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  mat4 r = mat4_identity();
  r.m[0] = c;
  r.m[2] = s;
  r.m[8] = -s;
  r.m[10] = c;
  return r;
}

inline mat4 mat4_rotate_x(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  mat4 r = mat4_identity();
  r.m[5] = c;
  r.m[6] = -s;
  r.m[9] = s;
  r.m[10] = c;
  return r;
}

inline mat4 mat4_perspective(float fov_rad, float aspect, float near_plane,
                             float far_plane) {
  float f = 1.0f / std::tan(fov_rad / 2.0f);
  float nf = 1.0f / (near_plane - far_plane);
  mat4 r = {};
  r.m[0] = f / aspect;
  r.m[5] = f;
  r.m[10] = (far_plane + near_plane) * nf;
  r.m[11] = -1.0f;
  r.m[14] = 2.0f * far_plane * near_plane * nf;
  return r;
}

inline mat4 mat4_look_at(vec3 eye, vec3 center, vec3 up) {
  vec3 f = vec3_normalize(vec3_sub(center, eye));
  vec3 s = vec3_normalize(vec3_cross(f, up));
  vec3 u = vec3_cross(s, f);

  mat4 r = mat4_identity();
  r.m[0] = s.x;
  r.m[1] = u.x;
  r.m[2] = -f.x;

  r.m[4] = s.y;
  r.m[5] = u.y;
  r.m[6] = -f.y;

  r.m[8] = s.z;
  r.m[9] = u.z;
  r.m[10] = -f.z;

  r.m[12] = -vec3_dot(s, eye);
  r.m[13] = -vec3_dot(u, eye);
  r.m[14] = vec3_dot(f, eye);
  return r;
}

} // namespace alg
