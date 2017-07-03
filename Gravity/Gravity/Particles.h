#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>
#include <unordered_set>
#include "vec2.h"
#include "Particle.h"

using std::vector;
using chrom::vec2;
using chrom::Particle;
using std::unordered_set;

namespace chrom{
    class Particles
    {
    public:
        void add_particle(float mass, float radius, const vec2f& position, const vec2f& velocity = { 0, 0 });
        long long remove_colliding_particles();
        const vector<Particle>& get_partcles() const;
        vector<Particle>& get_particles();

    private:
        unordered_set<int> id_removal_list;
        vector<Particle> particles;

        void collect_colliding_particles();
    };
}

#endif
