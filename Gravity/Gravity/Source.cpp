#include "ParticleSystem.h"
#include "Trig.h"
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>

using chrom::vec2f;

void update(int);
void keyboard(unsigned char key, int x, int y);
void mouse_motion(int x, int y);
void mouse(int button, int state, int x, int y);
void display();

struct Preset {
  float mass;
  float radius;
};

ParticleSystem prt_system;
vec2f x1, x2, M;
bool LEFT_PRESSED = false;

constexpr float Pi = 3.14159265358979323846f;

const Preset small_planet{60, cbrt(3 * 60 / (4 * 0.5f * Pi))},
    big_planet{700, cbrt(3 * 700 / (4 * 0.5f * Pi))},
    super_nova{6000, cbrt(3 * 6000 / (4 * 0.5f * Pi))};
Preset current = big_planet;

int main(int argc, char *argv[]) {
  Trig::initialize();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000, 1000);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Gravity");

  glClearColor(0, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-500.0, 500.0, 500.0, -500.0, 0, 1);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMotionFunc(mouse_motion);
  glutMouseFunc(mouse);
  glutTimerFunc(25, update, 0);
  glutMainLoop();
}

void update(int val) {
  prt_system.check_for_collisions();
  prt_system.time_step(0.5);
  glutPostRedisplay();
  glutTimerFunc(25, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case '1':
    current = small_planet;
    std::cout << "planet ( m = " << small_planet.mass
              << " kg, r = " << small_planet.radius << " m) \n";
    break;
  case '2':
    current = big_planet;
    std::cout << "planet ( m = " << big_planet.mass
              << " kg, r = " << big_planet.radius << " m) \n";
    break;
  case '3':
    current = super_nova;
    std::cout << "planet ( m = " << super_nova.mass
              << " kg, r = " << super_nova.radius << " m) \n";
    break;
  case 'u':
    prt_system.add_particle(20'000, cbrt(3 * 20'000 / (4 * 0.5f * Pi)), {0, 0});
    prt_system.add_particle(big_planet.mass, big_planet.radius, {150, 0},
                            {0, 15});
    break;
  case 'c':
    prt_system.remove_particles();
    break;
  case 27:
    exit(0);
  }
}

void mouse_motion(int x, int y) {
  M = {static_cast<float>(x - 500), static_cast<float>(y - 500)};

  if (LEFT_PRESSED)
    x2 = M;
}

void mouse(int button, int state, int x, int y) {
  M = {static_cast<float>(x - 500), static_cast<float>(y - 500)};

  switch (button) {
  case GLUT_LEFT_BUTTON:
    LEFT_PRESSED = state == GLUT_DOWN;
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN) {
      const auto pos = x1 == vec2f{0, 0} ? M : x1;
      const auto v = x1 - x2;
      prt_system.add_particle(current.mass, current.radius, pos, v);
      x1 = x2 = {0, 0};
    }
    break;
  }

  if (LEFT_PRESSED)
    x1 = x2 = M;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0, 1, 0);

  glBegin(GL_LINES);
  glVertex2f(x1.comp.x, x1.comp.y);
  glVertex2f(x2.comp.x, x2.comp.y);
  glEnd();

  for (const auto &p : prt_system.get_partcles()) {
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    for (auto a = 0.0f; a < 2 * Pi; a += 0.2)
      glVertex2f(p.radius * Trig::cos(a) + p.position.comp.x,
                 p.radius * Trig::sin(a) + p.position.comp.y);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(p.position.comp.x, p.position.comp.y);
    glVertex2f(p.position.comp.x + p.velocity.comp.x,
               p.position.comp.y + p.velocity.comp.y);
    glEnd();
  }

  glFlush();
  glutSwapBuffers();
}