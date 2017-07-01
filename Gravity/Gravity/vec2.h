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
        struct { T x, y; } coord;
        T v[2];

        vec2(T x = 0, T y = 0) : coord{ x, y } {};

        constexpr vec2 operator+(const vec2& other) const {
            return vec2{ v[0] + other.v[0], v[1] + other.v[1] };
        }

        constexpr vec2 operator-(const vec2& other) const {
            return vec2{ v[0] - other.v[0], v[1] - other.v[1] };
        }

        constexpr vec2 operator*(T scale) const {
            return vec2{ v[0] * scale, v[1] * scale };
        }

        constexpr vec2 operator*(const vec2& other) const {
            return vec2{ v[0] * other.v[0], v[1] * other.v[1] };
        }

        vec2& operator+=(const vec2& other) {
            coord.x += other.coord.x;
            coord.y += other.coord.y;
            return *this;
        }

        vec2& operator*=(const vec2& other){
            coord.x *= other.coord.x;
            coord.y *= other.coord.y;
            return *this;
        }

        constexpr bool operator==(const vec2& other) const{
            return coord.x == other.coord.x && coord.y == other.coord.y;
        }
        vec2 abs() const{
            return vec2{ std::abs(coord.x), std::abs(coord.y) };
        }

        double distance(const vec2& other) const {
            const auto dist0 = other.coord.x - coord.x;
            const auto dist1 = other.coord.y - coord.y;
            const auto sum_of_squares = dist0*dist0 + dist1*dist1;
            return sqrt(sum_of_squares);
        }

        double magnitude() const {
            return this->distance(vec2{ 0,0 });
        }

        auto angle() const {
            return atan2(coord.y, coord.x);
        }
    };
}

#endif
