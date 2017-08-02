#ifndef PARTICLES_H
#define PARTICLES_H

#include "Particle.h"
#include <unordered_set>
#include <vector>

using chrom::vec2f;
using std::unordered_set;
using std::vector;

namespace chrom {
class Particles {
public:
  void add_particle(float mass, float radius, const vec2f &position,
                    const vec2f &velocity = {0, 0});
  long long remove_colliding_particles();
  const vector<Particle> &get_partcles() const;
  vector<Particle> &get_particles();

private:
  unordered_set<int> id_removal_list;
  vector<Particle> particles;

  static vec2f perfectly_inelastic_collision(const Particle &p1,
                                             const Particle &p2);
  void collect_colliding_particles();
};
} // namespace chrom

#endif
