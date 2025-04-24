#include <iostream>
#include <GL/glut.h>

using namespace std;

int wl = 1200, wh = 700;  // Window size


// Initialization
void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(1,0,0);
    glPointSize(10.0);
    gluOrtho2D(-wl,wl,-wh,wh);

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2i(100,200);
    glEnd();
    glFlush();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Demo");

    glutDisplayFunc(display);
    myInit();

    glutMainLoop();
    return 0;
}
