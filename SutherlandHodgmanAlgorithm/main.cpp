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

struct Point {
    float x, y;
};

bool isInside(Point p, Point edgeStart, Point edgeEnd) {
    // Calculate the signed area of the triangle formed by the point p
    // and the two endpoints of the edge (edgeStart and edgeEnd)
    float area = (edgeEnd.x - edgeStart.x) * (p.y - edgeStart.y) -
                 (p.x - edgeStart.x) * (edgeEnd.y - edgeStart.y);

    // If the area is greater than or equal to 0, the point is inside the edge
    // Return true if inside, false otherwise
    return area >= 0;
}

void computeIntersection(Point p1, Point p2, Point edgeStart, Point edgeEnd, Point& intersection) {
    // Calculate the intersection point between the line segment defined by p1 and p2,
    // and the clipping edge defined by edgeStart and edgeEnd

    // Calculate the direction vectors of the line segments
    float dir1x = p2.x - p1.x;
    float dir1y = p2.y - p1.y;
    float dir2x = edgeEnd.x - edgeStart.x;
    float dir2y = edgeEnd.y - edgeStart.y;

    // Calculate the determinant
    float det = dir1x * dir2y - dir1y * dir2x;

    // Check if the line segments are not parallel
    if (det != 0) {
        // Calculate the parameter values for the line segments
        float t1 = ((edgeStart.y - p1.y) * dir2x - (edgeStart.x - p1.x) * dir2y) / det;
        float t2 = ((edgeStart.y - p1.y) * dir1x - (edgeStart.x - p1.x) * dir1y) / det;

        // Check if the intersection is within the line segments
        if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1) {
            // Calculate the intersection point
            intersection.x = p1.x + t1 * dir1x;
            intersection.y = p1.y + t1 * dir1y;
        }
    }
}

void clipPolygon(Point polygon[], int numVertices, Point clipWindow[], int numEdges) {
    Point tempPolygon[10];
    Point edgeStart, edgeEnd;

    for (int i = 0; i < numEdges; i++) {
        edgeStart = clipWindow[i];
        edgeEnd = clipWindow[(i + 1) % numEdges];

        int numTempVertices = 0;
        Point S = polygon[numVertices - 1];

        for (int j = 0; j < numVertices; j++) {
            Point P = polygon[j];

            if (isInside(P, edgeStart, edgeEnd)) {
                if (!isInside(S, edgeStart, edgeEnd)) {
                    Point intersection;
                    computeIntersection(S, P, edgeStart, edgeEnd, intersection);
                    tempPolygon[numTempVertices++] = intersection;
                }
                tempPolygon[numTempVertices++] = P;
            }
            else if (isInside(S, edgeStart, edgeEnd)) {
                Point intersection;
                computeIntersection(S, P, edgeStart, edgeEnd, intersection);
                tempPolygon[numTempVertices++] = intersection;
            }

            S = P;
        }

        numVertices = numTempVertices;
        for (int k = 0; k < numVertices; k++) {
            polygon[k] = tempPolygon[k];
        }
    }

    glColor3f(0.0f, 1.0f, 0.0f); // Green color for clipped polygon

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2f(polygon[i].x, polygon[i].y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Define the original polygon
    Point polygon[] = { {0.1f, 0.1f}, {0.3f, 0.9f}, {0.7f, 0.5f}, {0.9f, 0.1f} };
    int numVertices = sizeof(polygon) / sizeof(polygon[0]);

    // Define the clipping window
    Point clipWindow[] = { {0.2f, 0.2f}, {0.2f, 0.8f}, {0.8f, 0.8f}, {0.8f, 0.2f} };
    int numEdges = sizeof(clipWindow) / sizeof(clipWindow[0]);

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for original polygon

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2f(polygon[i].x, polygon[i].y);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for clipping window

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numEdges; i++) {
        glVertex2f(clipWindow[i].x, clipWindow[i].y);
    }
    glEnd();

    clipPolygon(polygon, numVertices, clipWindow, numEdges);

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
