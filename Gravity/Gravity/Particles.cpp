#include "Particles.h"

#include <iterator>
#include <algorithm>

using std::cbegin;
using std::cend;
using std::remove_if;
using std::distance;

void chrom::Particles::add_particle(float mass, float radius, const vec2<float>& position, const vec2<float>& velocity) {
    particles.emplace_back(Particle{ velocity, position, mass,radius });
}

void chrom::Particles::collect_colliding_particles()
{
    //for (auto i = 0; i < particles.size(); ++i){
    //    const auto& particle2 = particles[i];

    //    for (auto j = i + 1; j < particles.size(); ++j) {
    //        const auto& particle1 = particles[j];

    //        const auto distance = particle1.position.distance(particle2.position);
    //        if (distance < particle1.radius + particle2.radius)
    //            particles_to_erase.insert(&particle1);
    //    }
    //}

        for (auto i = 0; i < particles.size(); ++i){
        const auto& particle2 = particles[i];

        for (auto j = i + 1; j < particles.size(); ++j) {
            const auto& particle1 = particles[j];
            const auto distance = particle1.position.distance(particle2.position);
            if (distance < particle1.radius + particle2.radius)
                positions_to_erase.push_back(particle1.position);
        }
    }
}

long long chrom::Particles::remove_colliding_particles() {
    collect_colliding_particles();

    if (!positions_to_erase.empty()) {
        const auto remove_begin = remove_if(begin(particles), end(particles), [&](const Particle& particle) {
            //return particles_to_erase.find(&particle) != cend(particles_to_erase);
            return std::any_of(cbegin(positions_to_erase), cend(positions_to_erase), [&](const vec2<float>& position) { return particle.position == position; });
        });
        const auto deleted_particles = distance(remove_begin, end(particles));
        particles.erase(remove_begin, end(particles));
        //particles_to_erase.clear();
        positions_to_erase.clear();
        return deleted_particles;
    }

    return 0;
}

const vector<chrom::Particles::Particle>& chrom::Particles::get_partcles() const {
    return particles;
}

vector<chrom::Particles::Particle>& chrom::Particles::get_particles()
{
    return particles;
}
