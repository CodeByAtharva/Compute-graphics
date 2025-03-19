#include <iostream>
#include <GL/glut.h>
#include<math.h>

using namespace std;


int wl=1200;
int wh=700;
void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    gluOrtho2D(-wl,wl,-wh,wh);

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2i(250, 200); // Bottom-left
    glVertex2i(450, 200); // Bottom-right

    glVertex2i(450, 200); // Bottom-right
    glVertex2i(450, 350); // Top-right

    glVertex2i(450, 350); // Top-right
    glVertex2i(250, 350); // Top-left

    glVertex2i(250, 350); // Top-left
    glVertex2i(250, 200); // Bottom-left

    glEnd();

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
/*
    glutCreateMenu(menu);

    glutAddMenuEntry("simple line",1);
    glutAddMenuEntry("dashed line",2);
    glutAddMenuEntry("dotted line",3);
    glutAddMenuEntry("boat",4);
    glutAddMenuEntry("draw Axis",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);*/

    glutMainLoop();
    return 0;

}