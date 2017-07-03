#ifndef RUNGEKUTTA4_H
#define RUNGEKUTTA4_H

#include <array>
#include "Particles.h"

using std::array;
using chrom::Particle;

class RungeKutta4{
    using k_coeffs = std::array<vec2f, 4>;
    vector<k_coeffs> k_velocity;
    vector<k_coeffs> k_position;
    void reset_k_buffers();
    void copy_velocities_to_k_position(const vector<Particle>& particles);
    void calculate_first_k_velocity(const vector<Particle>& particles);
    void calculate_firt_k_position(const vector<Particle>& particles);
    void calculate_nth_k_velocity(const vector<Particle>& particles, int nth_coeff, float adjustment);
    void calculate_nth_k_position(const vector<Particle>& particles, int nth_coeff, float adjustment);
public:
    void resize_buffers(int size);
    void integrate(const vector<Particle>& particles, float time_step);
    void get_integration_result(vector<Particle>& particles, float time_step);
};

#endif

