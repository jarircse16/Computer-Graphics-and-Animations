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

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Set your transformations or load your modelview matrix here

    GLfloat modelviewMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set your transformations or load your projection matrix here

    GLfloat projectionMatrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

    // Printing the modelview matrix
    std::cout << "Modelview Matrix:\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << modelviewMatrix[i + j * 4] << " ";
        }
        std::cout << "\n";
    }

    // Printing the projection matrix
    std::cout << "Projection Matrix:\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << projectionMatrix[i + j * 4] << " ";
        }
        std::cout << "\n";
    }

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Window");

    // Set the display function
    glutDisplayFunc(display);

    // Enter the main loop
    glutMainLoop();

    return 0;
}
