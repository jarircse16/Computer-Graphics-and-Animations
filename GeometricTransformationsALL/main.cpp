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
using namespace std;


float translateX = 0.0f;
float translateY = 0.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;
float rotateAngle = 0.0f;



// Declare global variables
bool zoomIn = false;
bool zoomOut = false;
bool rotateLeft = false;
bool rotateRight = false;
bool translateUp = false;
bool translateDown = false;
bool translateLeft = false;
bool translateRight = false;



// Keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
    if (key == '+') {
        zoomIn = true;
    } else if (key == '-') {
        zoomOut = true;
    } else if (key == 'l') {
        rotateLeft = true;
    } else if (key == 'r') {
        rotateRight = true;
    } else if (key == 'u') {
        translateUp = true;
    } else if (key == 'd') {
        translateDown = true;
    } else if (key == 'f') {
        translateLeft = true;
    } else if (key == 'g') {
        translateRight = true;
    } else if (key == 'q') {
        exit(0);  // Terminate the program when 'q' is pressed
    }
}

// Update function for performing transformations
void update()
{
    if (zoomIn) {
        scaleX += 0.1f;
        scaleY += 0.1f;
        zoomIn = false;
    }
    if (zoomOut) {
        scaleX -= 0.1f;
        scaleY -= 0.1f;
        zoomOut = false;
    }
    if (rotateLeft) {
        rotateAngle += 5.0f;
        rotateLeft = false;
    }
    if (rotateRight) {
        rotateAngle -= 5.0f;
        rotateRight = false;
    }
    if (translateUp) {
        translateY += 0.1f;
        translateUp = false;
    }
    if (translateDown) {
        translateY -= 0.1f;
        translateDown = false;
    }
    if (translateLeft) {
        translateX -= 0.1f;
        translateLeft = false;
    }
    if (translateRight) {
        translateX += 0.1f;
        translateRight = false;
    }
}

///User Input Messages
void instructions()
{
    cout << "Please enter:" << endl;
    cout << "'+' to zoom in" << endl;
    cout << "'-' to zoom out" << endl;
    cout << "'l' to rotate left" << endl;
    cout << "'r' to rotate right" << endl;
    cout << "'u' to translate up" << endl;
    cout << "'d' to translate down" << endl;
    cout << "'f' to translate left" << endl;
    cout << "'g' to translate right" << endl;
    cout << "'q' to quit" << endl;
}

// Display function
void display()
{
    // Display instructions for user input

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(translateX, translateY, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);
    glRotatef(rotateAngle, 0.0f, 0.0f, 1.0f);

    // Set background color to green
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    // Draw a red square
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    glFlush();
}

// Timer function to update and redisplay
void timer(int)
{
    update();
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

int main(int argc, char** argv)
{
    instructions();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Transformation");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
