#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec2.h"

using chrom::vec2f;

namespace chrom {
struct Particle {
private:
  static int id_counter;

public:
  int id;
  vec2f velocity;
  vec2f position;
  float mass;
  float radius;

  Particle(const vec2f &v, const vec2f &p, float m, float r);
  Particle();
};
} // namespace chrom

#endif
