#include <iostream>
#include <GL/glut.h>
#include<math.h>

int wl=700;
int wh=700;
void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    gluOrtho2D(-wl,wl,-wh,wh);

}


void ddaAlgorithm(int x1,int y1,int x2,int y2, int LineType){

int l;
int dx=x2-x1;
int dy=y2-y1;

//to find out the length
if(abs(dx)>abs(dy)){
    l=dx;
}else{
    l=dy;
}


float DX = dx / float(l);
float DY = dy / float(l);

float x=x1;
float y=y1;



glBegin(GL_POINTS);
    for(int i=0;i<=l;i++){
        glColor3i(0,0,0);
        glVertex2i(round(x),round(y));
        x=x+DX;
        y=y+DY;
    }

    glEnd();
    glFlush();


}

void plotAxis(){
    glBegin(GL_LINES);
        glVertex2i(-wl,0); //
        glVertex2i(wl,0);



        glVertex2i(0,-wh);
        glVertex2i(0,wh);
    glEnd();
    glFlush();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    ddaAlgorithm(100,100,200,200);

    int c;
    cout<<"\nEnter your choice:";
    cout<<"1. simple line";
    cout<<"2. dotted line";
    cout<<"3. Dashed line";
    cout<<"4. Boat object";
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