#include <iostream>
#include <GL/glut.h>


int x1, y1, x2, y2;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine() {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;

    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }

    int D = 2 * dy - dx;
    int y = y1;

    for (int x = x1; x <= x2; x++) {
        drawPixel(x, y);

        if (D > 0) {
            y += yi;
            D -= 2 * dx;
        }

        D += 2 * dy;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    drawLine();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char** argv) {
    std::cout << "Enter the coordinates of the first point (x1, y1): ";
    std::cin >> x1 >> y1;
    std::cout << "Enter the coordinates of the second point (x2, y2): ";
    std::cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
