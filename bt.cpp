#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int wl = 1200;
int wh = 700;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3i(0, 0, 0);
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    //glPushMatrix(); // use to save the current transformation matrix onto a stack this function is deprecated from the opengl

    // Apply transformations
    glTranslatef(tx, ty, 0); // Translation
    glScalef(sx, sy, 1);     // Scaling
    glRotatef(angle, 0, 0, 1); // Rotation
    glBegin(GL_LINES);

    // Draw a rectangle
    glVertex2i(250, 200); // Bottom-left
    glVertex2i(450, 200); // Bottom-right

    glVertex2i(450, 200); // Bottom-right
    glVertex2i(450, 350); // Top-right

    glVertex2i(450, 350); // Top-right
    glVertex2i(250, 350); // Top-left

    glVertex2i(250, 350); // Top-left
    glVertex2i(250, 200); // Bottom-left

    glEnd();

    glPopMatrix();
    glFlush();

}





int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,50);
    glutCreateWindow("Transformation");

    glutDisplayFunc(display);
    myInit();

    // Create menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Translation", 1);
    glutAddMenuEntry("Scaling", 2);
    glutAddMenuEntry("Rotation", 3);
    glutAddMenuEntry("Rotation about arbitrary point", 4);
    glutAddMenuEntry("Scaling about fixed point", 5);
    glutAddMenuEntry("Reflection", 6);
    glutAddMenuEntry("Shear", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}