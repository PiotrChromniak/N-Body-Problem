#include "Verlet.h"

void Verlet::resize_buffers(int size) {
  accelerations.resize(size);
  next_accelerations.resize(size);
}

void Verlet::reset_buffer() {
  fill(begin(accelerations), end(accelerations), vec2f{0, 0});
  fill(begin(next_accelerations), end(next_accelerations), vec2f{0, 0});
}

void Verlet::calculate_accelerations(const vector<chrom::Particle> &particles,
                                     vector<vec2f> &output) {
#define PI 3.14159265358979323846
  for (size_t y = 0; y < particles.size(); ++y) {
    const auto &particle2 = particles[y];

    for (auto x = y + 1; x < particles.size(); ++x) {
      const auto &particle1 = particles[x];

      auto distance = chrom::distance(particle2.position, particle1.position);
      auto dist_vector = particle2.position - particle1.position;
      double angle[]{dist_vector.angle(), angle[0] + PI};
      auto partial_acceleration = 1.0f / (distance * distance);

      output[x] +=
          vec2f{static_cast<float>(particle2.mass * partial_acceleration *
                                   cos(angle[0])),
                static_cast<float>(particle2.mass * partial_acceleration *
                                   sin(angle[0]))};

      output[y] +=
          vec2f{static_cast<float>(particle1.mass * partial_acceleration *
                                   cos(angle[1])),
                static_cast<float>(particle1.mass * partial_acceleration *
                                   sin(angle[1]))};
    }
  }
#undef PI
}

void Verlet::integrate(vector<chrom::Particle> &particles, float time_step) {
  reset_buffer();
  calculate_accelerations(particles, accelerations);
  for (size_t i = 0; i < particles.size(); ++i) {
    auto &part = particles[i];
    part.position +=
        (part.velocity + accelerations[i] * time_step * 0.5f) * time_step;
  }
  calculate_accelerations(particles, next_accelerations);
  for (size_t i = 0; i < particles.size(); ++i) {
    auto &part = particles[i];
    part.velocity +=
        (accelerations[i] + next_accelerations[i]) * 0.5f * time_step;
  }
}
