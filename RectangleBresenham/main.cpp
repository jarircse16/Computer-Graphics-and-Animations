#include <windows.h>
#include <iostream>
#include <time.h>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>

using namespace std;

int x1, y1, x2, y2, x3, y3, x4, y4;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle() {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x4, y4);
    drawLine(x4, y4, x1, y1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    drawRectangle();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // Set the coordinate system
}

int main(int argc, char** argv) {
    cout << "Enter the coordinates of the four corners of the rectangle:\n";
    cout << "Point 1 (x1, y1): ";
    cin >> x1 >> y1;
    cout << "Point 2 (x2, y2): ";
    cin >> x2 >> y2;
    cout << "Point 3 (x3, y3): ";
    cin >> x3 >> y3;
    cout << "Point 4 (x4, y4): ";
    cin >> x4 >> y4;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Rectangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
