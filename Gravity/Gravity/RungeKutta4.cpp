#include "RungeKutta4.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using std::sin;
using std::cos;

void RungeKutta4::reset_k_buffers()
{
    for (size_t i = 0; i < k_position.size(); ++i)
        for (auto& k : k_position[i])
            k = { 0,0 };

    for (size_t i = 0; i < k_velocity.size(); ++i)
        for (auto& k : k_velocity[i])
            k = { 0,0 };
}

void RungeKutta4::copy_velocities_to_k_position(const vector<Particles::Particle>& particles)
{
    for (size_t i = 0; i < particles.size(); ++i) {
        const auto& velocity = particles[i].velocity;
        for (auto& k : k_position[i])
            k = velocity;
    }

}

void RungeKutta4::resize_buffers(int size)
{
    acceleration_buffer.resize(size);
    k_velocity.resize(size);
    k_position.resize(size);
}

void RungeKutta4::calculate_first_k_velocity(const vector<chrom::Particles::Particle>& particles) {
    for (size_t y = 0; y < particles.size(); ++y) {
        const auto& particle2 = particles[y];

        for (auto x = y + 1; x < particles.size(); ++x) {
            const auto& particle1 = particles[x];

            const auto distance = particle2.position.distance(particle1.position);
            const auto dist_vector = particle2.position - particle1.position;
            const double angle[]{ dist_vector.angle(), angle[0] + M_PI };
            const auto partial_acceleration = 0.5f / (distance*distance);

            acceleration_buffer[x]/*k_velocity[x][0]*/ += vec2<float>{ static_cast<float>(particle2.mass * partial_acceleration * cos(angle[0])),
                static_cast<float>(partial_acceleration * particle2.mass * sin(angle[0]))};

            acceleration_buffer[y]/*k_velocity[y][0]*/ += vec2<float>{ static_cast<float>(particle1.mass * partial_acceleration * cos(angle[1])),
                static_cast<float>(partial_acceleration * particle1.mass * sin(angle[1]))};

        }
    }
    //TODO throw out the acceleration buffer - you write to k_velocity anyway
    for (size_t i = 0; i < acceleration_buffer.size(); ++i)
        k_velocity[i][0] = acceleration_buffer[i];
}

void RungeKutta4::calculate_firt_k_position(const vector<chrom::Particles::Particle>& particles)
{
    for (size_t i = 0; i < k_velocity.size(); ++i)
        k_velocity[i][0] = particles[i].velocity;
}

void RungeKutta4::calculate_nth_k_velocity(const vector<Particles::Particle>& particles, int nth_coeff, float adjustment)
{
    for (size_t y = 0; y < particles.size(); ++y) {

        const auto& part2 = particles[y];
        auto k_p = k_position[y];
        const auto adjusted_position = part2.position + k_p[nth_coeff - 1] * adjustment;

        for (auto x = y + 1; x < particles.size(); ++x) {
            const auto& part1 = particles[x];

            const auto distance = adjusted_position.distance(part1.position);
            const auto dist_vector = adjusted_position - part1.position;
            const double angle[]{ dist_vector.angle(), angle[0] + M_PI };
            const auto partial_acceleration = 0.5f / (distance*distance); //TODO apply G constant

            k_velocity[x][nth_coeff] += vec2<float>{ static_cast<float>(part2.mass * partial_acceleration * cos(angle[0])),
                static_cast<float>(partial_acceleration * part2.mass * sin(angle[0]))};

            k_velocity[y][nth_coeff] += vec2<float>{ static_cast<float>(part1.mass * partial_acceleration * cos(angle[1])),
                static_cast<float>(partial_acceleration * part1.mass * sin(angle[1]))};
        }
    }
}

void RungeKutta4::calculate_nth_k_position(const vector<Particles::Particle>& particles, int nth_coeff, float adjustment)
{
    for (size_t i = 0; i < particles.size(); ++i){
        const auto g = k_velocity[i][nth_coeff - 1] * adjustment;
        k_position[i][nth_coeff] *= g.abs(); //TODO wtf actually xD using abs so further multiplication don't change the signs of vector components
    }
        
}

void RungeKutta4::integrate(const vector<Particles::Particle>& particles, float time_step)
{
    reset_k_buffers();
    copy_velocities_to_k_position(particles);
    calculate_first_k_velocity(particles);

    calculate_nth_k_velocity(particles, 1, time_step / 2);
    calculate_nth_k_position(particles, 1, time_step / 2);

    calculate_nth_k_velocity(particles, 2, time_step / 2);
    calculate_nth_k_position(particles, 2, time_step / 2);

    calculate_nth_k_velocity(particles, 3, time_step);
    calculate_nth_k_position(particles, 3, time_step);
}

void RungeKutta4::get_integration_result(vector<Particles::Particle>& particles, float time_step)
{
    const auto coeff = time_step / 6;
    for (size_t i = 0; i < particles.size(); ++i){
        auto& current_particle = particles[i];
        const auto& k_v = k_velocity[i];
        current_particle.velocity += (k_v[0] + k_v[1]*2 + k_v[2]*2 + k_v[3]) * coeff;
        const auto& k_p = k_position[i];
        current_particle.position += (k_p[0] + k_p[1] * 2 + k_p[2] * 2 + k_p[3]) * coeff;
    }   
}
