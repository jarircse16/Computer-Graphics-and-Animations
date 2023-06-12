#include <windows.h>
#include <iostream>
#include <time.h>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>

// Set the fill color
float fill_color[3] = { 1.0, 0.0, 0.0 };  // Red color

// Set the boundary color
float boundary_color[3] = { 0.0, 0.0, 0.0 };  // Black color

// Set the background color
float bg_color[3] = { 1.0, 1.0, 1.0 };  // White color

// Get the color at a specific pixel
void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

// Set the color at a specific pixel
void setPixelColor(int x, int y, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Define the flood fill function
void floodFill(int x, int y, float fillColor[3], float borderColor[3]) {
    float current_color[3];
    getPixelColor(x, y, current_color);

    // Check if the current pixel is not boundary color and not fill color
    if ((current_color[0] != fillColor[0] || current_color[1] != fillColor[1] || current_color[2] != fillColor[2]) &&
        (current_color[0] != borderColor[0] || current_color[1] != borderColor[1] || current_color[2] != borderColor[2])) {

        setPixelColor(x, y, fillColor);

        // Recursively fill the adjacent pixels
        floodFill(x + 1, y, fillColor, borderColor);
        floodFill(x - 1, y, fillColor, borderColor);
        floodFill(x, y + 1, fillColor, borderColor);
        floodFill(x, y - 1, fillColor, borderColor);
    }
}

// Define the display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the background
    glColor3fv(bg_color);
    glBegin(GL_POLYGON);
    glVertex2i(100, 100);
    glVertex2i(200, 100);
    glVertex2i(200, 200);
    glVertex2i(100, 200);
    glEnd();

    // Draw the boundary of the region
    glColor3fv(boundary_color);
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(200, 100);
    glVertex2i(200, 200);
    glVertex2i(100, 200);
    glEnd();

    glFlush();

    // Automatically fill the region
    int start_x = 150;  // Starting x-coordinate for flood fill
    int start_y = 150;  // Starting y-coordinate for flood fill
    floodFill(start_x, start_y, fill_color, boundary_color);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Boundary Fill Algorithm");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 400, 0, 400);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
