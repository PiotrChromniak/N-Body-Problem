#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Verlet.h"

using chrom::vec2f;
using chrom::Particles;
using chrom::Particle;

class ParticleSystem
{
    Particles prt;
public:
    Verlet solver2;
    void add_particle(float mass, float radius, const vec2f& position, const vec2f& velocity = vec2f{0,0});
    void remove_particles();
    void time_step(float step);
    void check_for_collisions();
    const vector<Particle>& get_partcles() const;
};
#endif
