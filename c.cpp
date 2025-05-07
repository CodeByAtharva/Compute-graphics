#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;
int iter;
#define wl 1200
#define wh 700
void koch(float x1,float y1,float x2,float y2,int i){
    if(i==0){
       // glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        return;
    }

    float dx=(x2-x1)/3;
    float dy=(y2-y1)/3;
    float x3=x1+dx;
    float y3=y1+dy;
    float x5=x2-dx;
    float y5=y2-dy;

    float x4=0.5*(x1+x2)-sqrt(3.0)*(y1-y2)/6;
    float y4=0.5*(y1+y2)-sqrt(3.0)*(x2-x1)/6;

    koch(x1,y1,x3,y3,i-1);
    koch(x3,y3,x4,y4,i-1);
    koch(x4,y4,x5,y5,i-1);
    koch(x5,y5,x2,y2,i-1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x1=-0.5,y1=-0.3;
    float x2=0.5,y2=-0.3;
    float x3=0.0,y3=0.5;

    glBegin(GL_LINES);
    koch(x1,y1,x2,y2,iter);
    koch(x2,y2,x3,y3,iter);
    koch(x3,y3,x1,y1,iter);
    glEnd();
    glFlush();
}

void myInit(){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluOrtho2D(-1, 1, -1, 1);  
}
int main(int c,char** v){
    cout<<"Enter number of iteration's:";
    cin>>iter;
    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,200);

    glutCreateWindow("Koch curve");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
}