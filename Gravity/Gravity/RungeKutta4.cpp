#include "RungeKutta4.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using std::sin;
using std::cos;

void RungeKutta4::reset_state()
{
    fill(begin(dvdt), end(dvdt), derivatives{});
    fill(begin(drdt), end(drdt), derivatives{});
}

void RungeKutta4::save_initial_position(const vector<Particle>& particles)
{
    std::transform(cbegin(particles), cend(particles), begin(position), [&](const Particle& part)
    {
        return part.position;
    });
}

void RungeKutta4::move_particles(vector<Particle>& particles, int nth_derivative, float dt)
{
    auto index = nth_derivative - 1;
    for (size_t i = 0; i < particles.size(); ++i)
        particles[i].position = position[i] + drdt[i][index] * dt;
}

void RungeKutta4::copy_velocities_to_drdt(const vector<Particle>& particles)
{
    for (size_t i = 0; i < particles.size(); ++i) {
        const auto& velocity = particles[i].velocity;
        for (auto& k : drdt[i])
            k = velocity;
    }
}

void RungeKutta4::resize_buffers(int size)
{
    dvdt.resize(size);
    drdt.resize(size);
    position.resize(size);
}

void RungeKutta4::calculate_first_dvdt(const vector<Particle>& particles) {
    for (size_t y = 0; y < particles.size(); ++y) {
        const auto& particle2 = particles[y];

        for (auto x = y + 1; x < particles.size(); ++x) {
            const auto& particle1 = particles[x];

            auto distance = chrom::distance(particle2.position, particle1.position);
            auto dist_vector = particle2.position - particle1.position;
            double angle[]{ dist_vector.angle(), angle[0] + M_PI };
            auto partial_acceleration = 1.0f / (distance*distance);

            dvdt[x][0] += vec2f{ 
                static_cast<float>(particle2.mass * partial_acceleration * cos(angle[0])),
                static_cast<float>(particle2.mass * partial_acceleration * sin(angle[0]))
            };

            dvdt[y][0] += vec2f{ 
                static_cast<float>(particle1.mass * partial_acceleration * cos(angle[1])),
                static_cast<float>(particle1.mass * partial_acceleration * sin(angle[1]))
            };
        }
    }
}

void RungeKutta4::calculate_nth_dvdt(const vector<Particle>& particles, int nth_derivative)
{
    for (size_t y = 0; y < particles.size(); ++y) {
        const auto& part2 = particles[y];

        for (auto x = y + 1; x < particles.size(); ++x) {
            const auto& part1 = particles[x];

            auto distance = chrom::distance(part2.position, part1.position);
            auto dist_vector = part2.position - part1.position;
            double angle[]{ dist_vector.angle(), angle[0] + M_PI };
            auto partial_acceleration = 1.0f / (distance*distance);

            dvdt[x][nth_derivative] += vec2f{ 
                static_cast<float>(part2.mass * partial_acceleration * cos(angle[0])),
                static_cast<float>(part2.mass * partial_acceleration * sin(angle[0])) 
            };

            dvdt[y][nth_derivative] += vec2f{ 
                static_cast<float>(part1.mass * partial_acceleration * cos(angle[1])),
                static_cast<float>(part1.mass * partial_acceleration * sin(angle[1])) 
            };
        }
    }
}

void RungeKutta4::calculate_nth_drdt(const vector<Particle>& particles, int nth_derivative, float dt)
{
    auto index = nth_derivative - 1;
    for (size_t i = 0; i < particles.size(); ++i) {
        const auto g = dvdt[i][nth_derivative - 1];
        drdt[i][nth_derivative] += dvdt[i][index] * dt;
    }

}

void RungeKutta4::integrate(vector<Particle>& particles, float dt)
{
    reset_state();
    save_initial_position(particles);

    copy_velocities_to_drdt(particles);
    calculate_first_dvdt(particles);

    move_particles(particles, 1, dt / 2);
    calculate_nth_dvdt(particles, 1);
    calculate_nth_drdt(particles, 1, dt / 2);

    move_particles(particles, 2, dt / 2);
    calculate_nth_dvdt(particles, 2);
    calculate_nth_drdt(particles, 2, dt / 2);

    move_particles(particles, 3, dt);
    calculate_nth_dvdt(particles, 3);
    calculate_nth_drdt(particles, 3, dt);

    get_integration_result(particles, dt);
}

void RungeKutta4::get_integration_result(vector<Particle>& particles, float dt)
{
    const auto coeff = dt / 6;
    for (size_t i = 0; i < particles.size(); ++i) {
        auto& current_particle = particles[i];

        auto& dVdT = dvdt[i];
        current_particle.velocity += (dVdT[0] + (dVdT[1] + dVdT[2]) * 2 + dVdT[3]) * coeff;

        auto& dRdT = drdt[i];
        current_particle.position = position[i] + (dRdT[0] + (dRdT[1] + dRdT[2]) * 2 + dRdT[3]) * coeff;
    }
}
