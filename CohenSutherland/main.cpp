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

const int INSIDE = 0; // Bit code for the inside region of the window
const int LEFT = 1;   // Bit code for the left region of the window
const int RIGHT = 2;  // Bit code for the right region of the window
const int BOTTOM = 4; // Bit code for the bottom region of the window
const int TOP = 8;    // Bit code for the top region of the window

// Window boundaries
const float X_MIN = -0.8f;
const float X_MAX = 0.8f;
const float Y_MIN = -0.8f;
const float Y_MAX = 0.8f;

// Bitwise OR operation to combine the region codes of two endpoints
int computeOutCode(float x, float y)
{
    int code = INSIDE;

    if (x < X_MIN)
        code |= LEFT;
    else if (x > X_MAX)
        code |= RIGHT;

    if (y < Y_MIN)
        code |= BOTTOM;
    else if (y > Y_MAX)
        code |= TOP;

    return code;
}

// Clip the line segment using the Cohen-Sutherland algorithm
void clipLine(float x1, float y1, float x2, float y2)
{
    int outcode1 = computeOutCode(x1, y1);
    int outcode2 = computeOutCode(x2, y2);
    bool accept = false;

    while (true)
    {
        if ((outcode1 | outcode2) == 0)
        {
            // Both endpoints are inside the window
            accept = true;
            break;
        }
        else if ((outcode1 & outcode2) != 0)
        {
            // Both endpoints are outside the same region
            break;
        }
        else
        {
            // Some part of the line is inside the window
            int outcodeOut = outcode1 != 0 ? outcode1 : outcode2;
            float x, y;

            // Find the intersection point
            if (outcodeOut & TOP)
            {
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            }
            else if (outcodeOut & BOTTOM)
            {
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            }
            else if (outcodeOut & RIGHT)
            {
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            }
            else if (outcodeOut & LEFT)
            {
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }

            if (outcodeOut == outcode1)
            {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                outcode2 = computeOutCode(x2, y2);
            }
        }
    }

    if (accept)
    {
        // Draw the clipped line segment
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the window boundaries
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(X_MIN, Y_MIN);
    glVertex2f(X_MAX, Y_MIN);
    glVertex2f(X_MAX, Y_MAX);
    glVertex2f(X_MIN, Y_MAX);
    glEnd();

    // Clip and draw the line segments
    clipLine(-0.9f, 0.4f, 0.9f, -0.7f);
    clipLine(0.1f, 0.8f, -0.5f, -0.9f);
    clipLine(-0.3f, -0.5f, 0.7f, 0.5f);

    glFlush();
}

// Initialize OpenGL settings
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return 0;
}
