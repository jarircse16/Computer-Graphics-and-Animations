#include <windows.h>
#include <GL/glut.h>
#include <cmath>

// Circle center and radius
GLfloat center_x = 0;
GLfloat center_y = 0;
GLfloat radius = 0.5;

// Number of triangles to form the circle
int num_triangles = 36;

void draw_circle() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    GLfloat angle = 0.0;
    GLfloat angle_increment = 2.0 * 3.1415 / num_triangles;

    // Draw triangles to form the circle
    for (int i = 0; i < num_triangles; i++) {
        // Calculate the coordinates of the triangle's vertices
        GLfloat x1 = center_x + radius * cos(angle);
        GLfloat y1 = center_y + radius * sin(angle);
        GLfloat x2 = center_x + radius * cos(angle + angle_increment);
        GLfloat y2 = center_y + radius * sin(angle + angle_increment);
        GLfloat x3 = center_x;
        GLfloat y3 = center_y;

        // Assign a color to each vertex
        glColor3f((x1 + 1) / 2, (y1 + 1) / 2, 0.5);
        glVertex2f(x1, y1);
        glColor3f((x2 + 1) / 2, (y2 + 1) / 2, 0.5);
        glVertex2f(x2, y2);
        glColor3f((x3 + 1) / 2, (y3 + 1) / 2, 0.5);
        glVertex2f(x3, y3);

        angle += angle_increment;
    }

    glEnd();
    glFlush();
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    draw_circle();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Circle with Colored Triangles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
