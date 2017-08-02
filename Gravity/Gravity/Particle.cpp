#include "Particle.h"

int chrom::Particle::id_counter = 0;

chrom::Particle::Particle(const vec2f &v, const vec2f &p, float m, float r)
    : id(id_counter++), velocity(v), position(p), mass(m), radius(r) {}

chrom::Particle::Particle()
    : id(-1), velocity({0, 0}), position({0, 0}), mass(-1), radius(-1) {}
