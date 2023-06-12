#include <windows.h>
#include <iostream>
#include <time.h>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>


// Set the dimensions of the grid
const int ROWS = 8;
const int COLS = 8;

// Define the grid
int grid[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

// Set the dimensions of the window
const int WIDTH = COLS * 50;
const int HEIGHT = ROWS * 50;

// Set the colors
float bgColor[3] = { 1.0, 1.0, 1.0 };            // Background color (white)
float targetColor[3] = { 0.0, 0.0, 0.0 };        // Target color (black)
float fillColor[3] = { 1.0, 0.0, 0.0 };          // Fill color (red)

// Function to draw a cell
void drawCell(int row, int col) {
    if (grid[row][col] == 1) {
        glColor3fv(targetColor);    // Draw boundary color
    }
    else {
        glColor3fv(fillColor);      // Draw fill color
    }

    glRectf(col * 50, row * 50, (col + 1) * 50, (row + 1) * 50);
}

// Function to perform flood fill
void floodFill(int row, int col) {
    // Check if the current cell is within the grid and has the target color
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || grid[row][col] != 0) {
        return;
    }

    // Set the current cell to the fill color
    grid[row][col] = 2;

    // Draw the updated cell
    drawCell(row, col);

    // Recursively perform flood fill on adjacent cells
    floodFill(row - 1, col); // Up
    floodFill(row + 1, col); // Down
    floodFill(row, col - 1); // Left
    floodFill(row, col + 1); // Right
}

// Function to display the grid
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            drawCell(i, j);
        }
    }

    glFlush();
}

// Function to handle mouse click event
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert mouse coordinates to grid cell
        int row = y / 50;
        int col = x / 50;

        // Perform flood fill starting from the clicked cell
        floodFill(row, col);
    }
}

// Function to initialize OpenGL
void init() {
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Flood Fill Algorithm");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}
