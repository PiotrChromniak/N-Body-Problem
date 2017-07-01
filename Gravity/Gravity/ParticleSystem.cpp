#include "ParticleSystem.h"

void ParticleSystem::add_particle(float mass, float radius, const vec2<float>& position, const vec2<float>& velocity)
{
    prt.add_particle(mass, radius, position, velocity);
    solver.resize_buffers(prt.get_partcles().size());
}

void ParticleSystem::remove_particles()
{
    prt.get_particles().resize(0);
    solver.resize_buffers(0);
}

void ParticleSystem::time_step(float step)
{
    solver.integrate(prt.get_partcles(), step);
    solver.get_integration_result(prt.get_particles(), step);
}

void ParticleSystem::check_for_collisions()
{
    const auto deleted_count = prt.remove_colliding_particles();
    if (deleted_count > 0){
        const auto prev_size = prt.get_partcles().size();
        prt.get_particles().resize(prev_size - deleted_count);
        solver.resize_buffers(prev_size - deleted_count);
    }   
}

const vector<chrom::Particles::Particle>& ParticleSystem::get_partcles() const
{
    return prt.get_partcles();
}
