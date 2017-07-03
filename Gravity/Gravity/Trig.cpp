#include "Trig.h"
#include <cmath>

double Trig::cos(double radians)
{
    constexpr auto Pi_2 = 3.14159265358979323846 / 2;
    const auto sign = radians < 0 ? -1 : 1;
    const auto rad = std::abs(radians);
    const auto quater = static_cast<int>(rad / Pi_2) % 4;

    return 0.0;
}
