#include <iostream>
#include <GL/glut.h>


int wl=1400;
int wh=900;

void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    gluOrtho2D(-wl,wl,-wh,wh);

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

}

int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,50);
    glutCreateWindow("DDA Assignment 1");

    glutDisplayFunc(display);
    myInit();



    glutMainLoop();
    return 0;

}