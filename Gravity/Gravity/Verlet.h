#ifndef VERLET_H
#define VERLET_H

#include "Particles.h"

class Verlet
{
    vector<vec2f> accelerations;
    vector<vec2f> next_accelerations;
    void reset_buffer();
    static void calculate_accelerations(const vector<chrom::Particle>& particles, vector<vec2f>& output);
public:
    void integrate(vector<chrom::Particle>& particles, float time_step);
    void resize_buffers(int size);
};

#endif
