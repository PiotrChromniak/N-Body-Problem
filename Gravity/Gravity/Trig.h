#pragma once

#include <array>
class Trig
{
    static std::array<double, 500> sin_table;
    static std::array<double, 500> cos_table;
public:
    static double cos(double radians);
    static double sin(double radians);
};

