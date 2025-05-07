#include<iostream>
#include<GL/glut.h>
#include<cmath>

#define wl 1200
#define wh 700

void myInit(){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    gluOrtho2D(-wl,wl,-wh,wh);
}


void circle(int r,int h,int k){
    int d=3-(2*r);
    int x=0;
    int y=r;

    glBegin(GL_POINTS);
    while(x<=y){
        if(d<=0){
            d=d+4*x+6;
        }else{
            d=d+4*(x-y)+10;
            y--;
        }
        x++;

        glVertex2i(h+x,k+y);
        glVertex2i(h-x,k+y);
        glVertex2i(h+x,k-y);
        glVertex2i(h-x,k-y);


        glVertex2i(h+y,k+x);
        glVertex2i(h-y,k+x);
        glVertex2i(h+y,k-x);
        glVertex2i(h-y,k-x);
    }
    glEnd();
    glFlush();
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
    circle(200,0,0);
    circle(200,100,0);
}

int main(int c,char** v){
    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,200);

    glutCreateWindow("Bresenehem Circle");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
}