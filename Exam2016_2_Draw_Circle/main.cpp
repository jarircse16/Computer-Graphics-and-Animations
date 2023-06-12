#include <windows.h>
#include <time.h>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include<cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#include <iostream>
#include <GL/glut.h>

// Function to handle window resizing
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width/2, width/2, -height/2, height/2);
}

// Function to render (display) the scene
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // Set color to white

    const float radius = 100.0;  // Radius of the circle
    const int numSegments = 100; // Number of line segments to approximate the circle

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0 * M_PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }

    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Circle Drawing");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
