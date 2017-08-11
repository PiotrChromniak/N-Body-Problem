#ifndef VEC2_H
#define VEC2_H

#include <cmath>

using std::abs;
using std::atan2;
using std::is_arithmetic;
using std::sqrt;

namespace chrom {
template <typename T> union vec2 {
  static_assert(is_arithmetic<T>::value, "T must be arithmetic type");
  struct {
    T x, y;
  };
  T v[2];

  constexpr vec2 operator+(const vec2 &other) const {
    return vec2{v[0] + other.v[0], v[1] + other.v[1]};
  }

  constexpr vec2 operator-(const vec2 &other) const {
    return vec2{v[0] - other.v[0], v[1] - other.v[1]};
  }

  constexpr vec2 operator*(T scale) const {
    return vec2{v[0] * scale, v[1] * scale};
  }

  vec2 &operator+=(const vec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  vec2 &operator%=(const vec2 &other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }

  constexpr bool operator==(const vec2 &other) const {
    return x == other.x && y == other.y;
  }
  vec2 abs() const { return vec2{std::abs(x), std::abs(y)}; }

  double magnitude() const { return std::hypot(x, y); }

  auto angle() const { return atan2(y, x); }
};
using vec2f = vec2<float>;

template <typename T> double distance(const vec2<T> &v1, const vec2<T> &v2) {
  return std::hypot(v2.x - v1.x, v2.y - v1.y);
}
} // namespace chrom

#endif
