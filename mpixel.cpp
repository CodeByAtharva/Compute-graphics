#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int wl = 1200;
int wh = 700;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3i(1, 0, 0);
    glPointSize(5.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2i(-wl,0);
    glVertex2i(wl,0);
    glVertex2i(0,-wh);
    glVertex2i(0,wh);
    glEnd();
    glFlush();
}

void mouseClick(int button,int state, int x, int  y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        int x1=(x-wl/2);
        int y1=(wh/2-y);
        cout<<"x: "<<x1<<" y: "<<y1<<endl;
        glBegin(GL_POINTS);
        glVertex2i(x1,y1);
        glEnd();
        glFlush();
    }
    //glutPostRedisplay();
}



int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,50);
    glutCreateWindow("Transformation");

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    myInit();



    glutMainLoop();
    return 0;
}