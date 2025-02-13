#include <iostream>
#include <GL/glut.h>

int wl=700;
int wh=700;
void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(6.0);
    gluOrtho2D(-wl,wl,-wh,wh);

}

void plotAxis(){
    glBegin(GL_LINES);
        glVertex2i(-wl,0);
        glVertex2i(wl,0);
        glVertex2i(0,-wh);
        glVertex2i(0,wh);
    glEnd();
    glFlush();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    plotAxis();

}


int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,150);
    glutCreateWindow("DDA Assignment 1");

    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;

}