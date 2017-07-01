#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include "ParticleSystem.h"

void update(int);
void keyboard(unsigned char key, int x, int y);
void mouse_motion(int x, int y);
void mouse(int button, int state, int x, int y);
void display();

ParticleSystem prt_system;
vec2<float> x1, x2, M;
bool LEFT_PRESSED = false;

float _mass = 20.0f;
float _radius = 3;
constexpr float Pi = 3.14159265358979323846f;

int main(int argc, char* argv[]){

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

void update(int val){
    prt_system.time_step(0.5);
    prt_system.check_for_collisions();
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
    case '1':
        _mass = 700;
        _radius = 7;
        std::cout << "700\n";
        break;
    case '2':
        _mass = 20;
        _radius = 3;
        std::cout << "20\n";
        break;
    case 'c':
        prt_system.remove_particles();
        break;
    case 27:
        exit(0);
    }
}

void mouse_motion(int x, int y)
{
    M = { static_cast<float>(x - 500), static_cast<float>(y - 500) };

    if (LEFT_PRESSED)
        x2 = M;
}

void mouse(int button, int state, int x, int y)
{
    M = { static_cast<float>(x - 500), static_cast<float>(y - 500) };
    
    switch (button){
    case GLUT_LEFT_BUTTON:
        LEFT_PRESSED = state == GLUT_DOWN;
        break;
    case GLUT_RIGHT_BUTTON:
        if(state == GLUT_DOWN){
            const auto pos = (x1 == chrom::vec2<float>{ 0, 0 }) ? M : x1;
            const auto v = (x1 == vec2<float>{0, 0} && x2 == vec2<float>{0, 0}) ? vec2<float>{0, 0} : x1 - x2;
            prt_system.add_particle(_mass, _radius, pos, v);
            x1 = x2 = { 0,0 };
        }
        break;
    }      

   if(LEFT_PRESSED)
       x1 = x2 = M;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);

    glBegin(GL_LINES);
        glVertex2f(x1.coord.x, x1.coord.y);
        glVertex2f(x2.coord.x, x2.coord.y);
    glEnd();

    for(const auto& p : prt_system.get_partcles()){
        glBegin(GL_POLYGON);
        for (auto a = 0.0f; a < 2 * Pi; a += 0.5)
            glVertex2f(p.radius*cos(a) + p.position.coord.x, p.radius*sin(a) + p.position.coord.y);
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}