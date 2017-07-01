#ifndef RUNGEKUTTA4_H
#define RUNGEKUTTA4_H

#include <array>
#include "Particles.h"

using std::array;
using chrom::Particles;

class RungeKutta4{
    using k_coeffs = std::array<vec2<float>, 4>;
    const float G = 6.674083131e-10f;
    const float g = 1.0f;
    vector<vec2<float>> acceleration_buffer;
    vector<k_coeffs> k_velocity;
    vector<k_coeffs> k_position;
    void reset_k_buffers();
    void copy_velocities_to_k_position(const vector<Particles::Particle>& particles);
    void calculate_first_k_velocity(const vector<Particles::Particle>& particles);
    void calculate_firt_k_position(const vector<Particles::Particle>& particles);
    void calculate_nth_k_velocity(const vector<Particles::Particle>& particles, int nth_coeff, float adjustment);
    void calculate_nth_k_position(const vector<Particles::Particle>& particles, int nth_coeff, float adjustment);
public:
    void resize_buffers(int size);
    void integrate(const vector<Particles::Particle>& particles, float time_step);
    void get_integration_result(vector<Particles::Particle>& particles, float time_step);
};

#endif

