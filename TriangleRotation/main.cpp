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
// Angle variables for rotation
GLfloat angle1 = 0.0f;
GLfloat angle2 = 0.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // Rotate the first triangle clockwise by 2 degrees
    glRotatef(angle1, 0.0f, 0.0f, 1.0f);

    // Draw the first triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glPopMatrix();

    glPushMatrix();

    // Rotate the second triangle counterclockwise by 2 degrees
    glRotatef(angle2, 0.0f, 0.0f, 1.0f);

    // Draw the second triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.0f, -0.5f);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void update(int value)
{
    // Update the angles for rotation
    angle1 += 2.0f;
    angle2 -= 2.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Double Buffering");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}
