#include "Particles.h"

#include <algorithm>
#include <iterator>

using chrom::Particle;
using std::cbegin;
using std::cend;
using std::distance;
using std::remove_if;

void chrom::Particles::add_particle(float mass, float radius,
                                    const vec2f &position,
                                    const vec2f &velocity) {
  particles.emplace_back(Particle{velocity, position, mass, radius});
}

void chrom::Particles::collect_colliding_particles() {
#define PI 3.14159265358979323846
  for (size_t i = 0; i < particles.size(); ++i) {
    auto &part2 = particles[i];
    if (id_removal_list.find(part2.id) != cend(id_removal_list))
      continue;

    for (auto j = i + 1; j < particles.size(); ++j) {
      auto &part1 = particles[j];
      const auto dist = distance(part1.position, part2.position);
      if (dist < part1.radius + part2.radius) {
        auto new_radius =
            std::cbrt(3 * (part1.mass + part2.mass) / (4 * 0.5f * PI));
        auto velocity_after_collision =
            perfectly_inelastic_collision(part1, part2);
        if (part1.mass < part2.mass) {
          id_removal_list.insert(part1.id);
          part2.mass += part1.mass;
          part2.radius = new_radius;
          part2.velocity = velocity_after_collision;
        } else {
          id_removal_list.insert(part2.id);
          part1.mass += part2.mass;
          part1.radius = new_radius;
          part1.velocity = velocity_after_collision;
        }
      }
    }
  }
#undef PI
}

long long chrom::Particles::remove_colliding_particles() {
  collect_colliding_particles();

  if (!id_removal_list.empty()) {
    const auto remove_begin = remove_if(
        begin(particles), end(particles), [&](const Particle &particle) {
          return id_removal_list.find(particle.id) != cend(id_removal_list);
        });
    const auto deleted_particles = std::distance(remove_begin, end(particles));
    particles.erase(remove_begin, end(particles));
    id_removal_list.clear();
    return deleted_particles;
  }

  return 0;
}

vec2f chrom::Particles::perfectly_inelastic_collision(const Particle &p1,
                                                      const Particle &p2) {
  auto mass_sum = p1.mass + p2.mass;
  return p1.velocity * (p1.mass / mass_sum) +
         p2.velocity * (p2.mass / mass_sum);
}

const vector<Particle> &chrom::Particles::get_partcles() const {
  return particles;
}

vector<Particle> &chrom::Particles::get_particles() { return particles; }
