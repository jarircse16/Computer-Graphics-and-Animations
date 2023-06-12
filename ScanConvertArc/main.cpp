#include <windows.h>
#include <iostream>
#include <time.h>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include<cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int WIDTH = 800;
const int HEIGHT = 600;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void drawArc(int xc, int yc, int radius, float startAngle, float endAngle)
{
    glBegin(GL_POINTS);

    float angle = startAngle;
    while (angle <= endAngle)
    {
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        glVertex2i(xc + static_cast<int>(x + 0.5), yc + static_cast<int>(y + 0.5));

        angle += 0.01; // Adjust the step size for a smoother arc
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0); // Set color to white
    glPointSize(1.0); // Set point size to 1

    int xc = WIDTH / 2;
    int yc = HEIGHT / 2;
    int radius = 200;
    float startAngle = 0.0;
    float endAngle = 2 * M_PI;

    drawArc(xc, yc, radius, startAngle, endAngle);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Scan Convert Arc");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
