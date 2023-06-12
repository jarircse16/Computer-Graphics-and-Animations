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


// Define the window size
int width = 800;
int height = 600;

// Define the center and radius of the arc
int centerX = width / 2;
int centerY = height / 2;
int radius = 200;

// Define the start and end angles of the arc
float startAngle = 45.0f;
float endAngle = 135.0f;

// Function to draw the arc using polynomial method
void drawArc() {
    glColor3f(1.0f, 0.0f, 0.0f);  // Set color to red

    float angle = startAngle;
    float angleIncrement = 1.0f;  // Adjust the angle increment to control the smoothness

    glBegin(GL_POINTS);
    while (angle <= endAngle) {
        float radians = angle * M_PI / 180.0f;

        // Calculate the x and y coordinates using the polynomial method
        int x = centerX + radius * cos(radians);
        int y = centerY + radius * sin(radians);

        glVertex2i(x, y);

        angle += angleIncrement;
    }
    glEnd();
}

// Function to display the OpenGL scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    drawArc();

    glFlush();
}

int main(int argc, char** argv) {
    // Initialize GLUT and create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Arc Scan Conversion");

    // Set the display function
    glutDisplayFunc(display);

    // Set the clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}
