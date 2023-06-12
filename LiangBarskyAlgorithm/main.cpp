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

int x1, y1, x2, y2; // Line coordinates
int xMin, yMin, xMax, yMax; // Clipping window coordinates

// Function to draw a point
void drawPoint(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Liang-Barsky Line Clipping Algorithm
void clipLine(int x1, int y1, int x2, int y2)
{
    float t1 = 0, t2 = 1;
    int dx = x2 - x1;
    int dy = y2 - y1;

    int p[4] = { -dx, dx, -dy, dy };
    int q[4] = { x1 - xMin, xMax - x1, y1 - yMin, yMax - y1 };

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) {
            return;
        }

        float t = (float)q[i] / p[i];

        if (p[i] < 0) {
            if (t > t1) {
                t1 = t;
            }
        }
        else if (p[i] > 0) {
            if (t < t2) {
                t2 = t;
            }
        }
    }

    if (t1 < t2) {
        int xStart = x1 + t1 * dx;
        int yStart = y1 + t1 * dy;
        int xEnd = x1 + t2 * dx;
        int yEnd = y1 + t2 * dy;

        glColor3f(0.0f, 1.0f, 0.0f); // Green color for clipped line
        glBegin(GL_LINES);
        glVertex2i(xStart, yStart);
        glVertex2i(xEnd, yEnd);
        glEnd();
    }
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); // White color for clipping window

    glBegin(GL_LINE_LOOP);
    glVertex2i(xMin, yMin);
    glVertex2i(xMax, yMin);
    glVertex2i(xMax, yMax);
    glVertex2i(xMin, yMax);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for original line

    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    clipLine(x1, y1, x2, y2);

    glFlush();
}

// Initialize OpenGL settings
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(0, 800, 0, 600);
}

int main(int argc, char** argv)
{
    std::cout << "Enter the coordinates of the first point (x1, y1): ";
    std::cin >> x1 >> y1;

    std::cout << "Enter the coordinates of the second point (x2, y2): ";
    std::cin >> x2 >> y2;

    std::cout << "Enter the coordinates of the clipping window (xMin, yMin, xMax, yMax): ";
    std::cin >> xMin >> yMin >> xMax >> yMax;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Liang-Barsky Line Clipping Algorithm");
    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return 0;
}
