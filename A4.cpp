#include<iostream>
#include<GL/glut.h>
#include<cmath>

using namespace std;

#define wl 640
#define wh 480

float bcolor[3]={0,0,0},fcolor[3]={1,0,0},pixel[3];
bool ffill=true;

void myInit(){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-wl,wl,-wh,wh);
}

void setPixel(int x,int y){
    glColor3fv(fcolor);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void getPixel(int x,int y,float *pixel){
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pixel);
}

void bfill(int x,int y){
    if (x > wl || x < -wl || y > wh || y < -wh) return;
    getPixel(x,y,pixel);
    if(pixel[0]!=bcolor[0]  && pixel[1]!=bcolor[1] && pixel[2]!=bcolor[2] &&
    pixel[0]!=fcolor[0] && pixel[1]!=fcolor[1] && pixel[2]!=fcolor[2]){
        setPixel(x,y);
        bfill(x+1,y);
        bfill(x,y+1);
        bfill(x-1,y);
        bfill(x,y-1);
    }
}


void mouse(int button,int state,int x,int y){
    int X=x;
    int Y=wh-y;
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        bfill(X,Y);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    int x1=100,y1=100,x2=250,y2=250;
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
    glFlush();
}

int main(int c,char** v){
    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,200);

    glutCreateWindow("Fill");
    myInit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}