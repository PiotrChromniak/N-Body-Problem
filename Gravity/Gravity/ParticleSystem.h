#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include"RungeKutta4.h"
class ParticleSystem
{
    RungeKutta4 solver;
    Particles prt;
public:
    void add_particle(float mass, float radius, const vec2<float>& position, const vec2<float>& velocity = vec2<float>{0,0});
    void remove_particles();
    void time_step(float step);
    void check_for_collisions();
    const vector<chrom::Particles::Particle>& get_partcles() const;
};
#endif
