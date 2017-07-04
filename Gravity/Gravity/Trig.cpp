#include "Trig.h"

std::array<double, 1000> Trig::cosine{};
std::array<double, 1000> Trig::sine{};

double Trig::cos(double radians)
{
    constexpr auto _2Pi = 2 * 3.14159265358979323846;
    constexpr auto Pi_2 = 3.14159265358979323846 / 2;
    auto positive_rad = abs(radians);
    auto remainder_rad = fmod(positive_rad, _2Pi);
    auto idx = remainder_rad * 1000 / _2Pi;
    double integral_part;
    auto fraction = modf(idx, &integral_part);
    auto index = static_cast<int>(integral_part);

    return cosine[index] + fraction * (cosine[index + 1] - cosine[index]);
}

double Trig::sin(double radians)
{
    constexpr auto _2Pi = 2 * 3.14159265358979323846;
    constexpr auto Pi_2 = 3.14159265358979323846 / 2;
    auto sign = radians < 0 ? -1 : 1;
    auto positive_rad = abs(radians);
    auto remainder_rad = fmod(positive_rad, _2Pi);
    auto idx = remainder_rad * 1000 / _2Pi;
    double integral_part;
    auto fraction = modf(idx, &integral_part);
    auto index = static_cast<int>(integral_part);

    return (sine[index] + fraction * (sine[index+1]-sine[index])) * sign;
}

void Trig::initialize()
{
    auto dx = 2 * 3.14159265358979323846 / 1000;
    for (size_t i = 0; i < 1000; ++i) {
        cosine[i] = std::cos(i*dx);
        sine[i] = std::sin(i*dx);
    }
}
