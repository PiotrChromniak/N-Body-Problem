#ifndef RUNGEKUTTA4_H
#define RUNGEKUTTA4_H

#include <array>
#include "Particles.h"

using std::array;
using chrom::Particle;

class RungeKutta4{
    using derivatives = array<vec2f, 4>;
    vector<derivatives> dvdt;
    vector<derivatives> drdt;
    vector<vec2f> position;

    void reset_state();
    void save_initial_position(const vector<Particle>& particles);
    void move_particles(vector<Particle>& particles, int nth_derivative, float dt);
    void copy_velocities_to_drdt(const vector<Particle>& particles);
    void calculate_first_dvdt(const vector<Particle>& particles);
    void calculate_nth_dvdt(const vector<Particle>& particles, int nth_derivative);
    void calculate_nth_drdt(const vector<Particle>& particles, int nth_derivative, float dt);
public:
    void resize_buffers(int size);
    void integrate(vector<Particle>& particles, float dt);
    void get_integration_result(vector<Particle>& particles, float dt);
};

#endif

