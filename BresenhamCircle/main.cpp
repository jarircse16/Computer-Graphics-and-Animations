#include <windows.h>
#include <iostream>
#include <time.h>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>

using namespace std;

int centerX, centerY, radius;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawCircle() {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        drawPixel(centerX + x, centerY + y); // Octant 1
        drawPixel(centerX + y, centerY + x); // Octant 2
        drawPixel(centerX - y, centerY + x); // Octant 3
        drawPixel(centerX - x, centerY + y); // Octant 4
        drawPixel(centerX - x, centerY - y); // Octant 5
        drawPixel(centerX - y, centerY - x); // Octant 6
        drawPixel(centerX + y, centerY - x); // Octant 7
        drawPixel(centerX + x, centerY - y); // Octant 8

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    drawCircle();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // Set the coordinate system
}

int main(int argc, char** argv) {
    cout << "Enter the coordinates of the center of the circle:\n";
    cout << "X-coordinate: ";
    cin >> centerX;
    cout << "Y-coordinate: ";
    cin >> centerY;
    cout << "Enter the radius of the circle: ";
    cin >> radius;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
