#ifndef VEC2_H
#define VEC2_H

#include <cmath>

using std::sqrt;
using std::atan2;
using std::abs;
using std::is_arithmetic;

namespace chrom {
    template<typename T>
    union vec2 {
        static_assert(is_arithmetic<T>::value, "T must be arithmetic type");
        struct { T x, y; } comp;
        T v[2];

        constexpr vec2 operator+(const vec2& other) const {
            return vec2{ v[0] + other.v[0], v[1] + other.v[1] };
        }

        constexpr vec2 operator-(const vec2& other) const {
            return vec2{ v[0] - other.v[0], v[1] - other.v[1] };
        }

        constexpr vec2 operator*(T scale) const {
            return vec2{ v[0] * scale, v[1] * scale };
        }

        vec2& operator+=(const vec2& other) {
            comp.x += other.comp.x;
            comp.y += other.comp.y;
            return *this;
        }

        constexpr bool operator==(const vec2& other) const{
            return comp.x == other.comp.x && comp.y == other.comp.y;
        }
        vec2 abs() const{
            return vec2{ std::abs(comp.x), std::abs(comp.y) };
        }

        double magnitude() const {
            return std::hypot(comp.x, comp.y);
        }

        auto angle() const {
            return atan2(comp.y, comp.x);
        }
    };
    
    using vec2f = vec2<float>;

    template<typename T>
    double distance(const vec2<T>& v1, const vec2<T>& v2) {
        return std::hypot(v2.comp.x - v1.comp.x, v2.comp.y - v1.comp.y);
    }
}

#endif
