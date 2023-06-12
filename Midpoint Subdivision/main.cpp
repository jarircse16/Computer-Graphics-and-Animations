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

// Midpoint Subdivision Line Clipping Algorithm
void clipLine(int x1, int y1, int x2, int y2)
{
    bool accept = false;
    bool done = false;

    int code1 = 0, code2 = 0;
    int x, y;

    while (!done)
    {
        code1 = (x1 < xMin) << 3 | (x1 > xMax) << 2 | (y1 < yMin) << 1 | (y1 > yMax);
        code2 = (x2 < xMin) << 3 | (x2 > xMax) << 2 | (y2 < yMin) << 1 | (y2 > yMax);

        if (code1 == 0 && code2 == 0)
        {
            accept = true;
            done = true;
        }
        else if ((code1 & code2) != 0)
        {
            done = true;
        }
        else
        {
            int code = code1 ? code1 : code2;

            if (code & (1 << 3))
            {
                x = xMin;
                y = y1 + (y2 - y1) * (xMin - x1) / (x2 - x1);
            }
            else if (code & (1 << 2))
            {
                x = xMax;
                y = y1 + (y2 - y1) * (xMax - x1) / (x2 - x1);
            }
            else if (code & (1 << 1))
            {
                y = yMin;
                x = x1 + (x2 - x1) * (yMin - y1) / (y2 - y1);
            }
            else if (code & (1 << 0))
            {
                y = yMax;
                x = x1 + (x2 - x1) * (yMax - y1) / (y2 - y1);
            }

            if (code == code1)
            {
                x1 = x;
                y1 = y;
            }
            else
            {
                x2 = x;
                y2 = y;
            }
        }
    }

    if (accept)
    {
        glColor3f(0.0f, 1.0f, 0.0f); // Green color for clipped line
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
    else
    {
        glColor3f(1.0f, 0.0f, 0.0f); // Red color for rejected line
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
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
    glutCreateWindow("Midpoint Subdivision Line Clipping Algorithm");
    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return 0;
}
