#ifndef TRIG_H
#define TRIG_H

#include <array>

class Trig {
  static std::array<double, 1000> sine;
  static std::array<double, 1000> cosine;

public:
  static double cos(double radians);
  static double sin(double radians);
  static void initialize();
};

#endif TRIG_H
