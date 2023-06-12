#include<GL/gl.h>
#include<GL/glut.h>
#include<windows.h>
//Corrected code
void display(void);

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(250,250);
    glutInitWindowPosition(100,100);
    glutCreateWindow("hello");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
/*

glClearColor(0.0,0.0,0.0);
glClearDepth(1.0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
*/
