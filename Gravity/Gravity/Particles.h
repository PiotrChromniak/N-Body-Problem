#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>
#include "vec2.h"
#include <unordered_set>

using std::vector;
using chrom::vec2;
using std::unordered_set;

class RungeKutta4;

namespace chrom{
    class Particles
    {
        friend class RungeKutta4;
    public:
        struct Particle {
            vec2<float> velocity;
            vec2<float> position;
            float mass;
            float radius;

            bool operator==(const Particle& other) const{
                return mass == other.mass && radius == other.radius && velocity == other.velocity && position == other.position;
            }
        };
        void add_particle(float mass, float radius, const vec2<float>& position, const vec2<float>& velocity = { 0, 0 });
        long long remove_colliding_particles();
        const vector<Particle>& get_partcles() const;
        vector<Particle>& get_particles();

    private:
        //unordered_set<Particle const*> particles_to_erase;
        vector<vec2<float>> positions_to_erase;
        vector<Particle> particles;

        void collect_colliding_particles();
    };
}

#endif
