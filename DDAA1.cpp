#include <iostream>
#include <GL/glut.h>
#include<math.h>

using namespace std;


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
    l=abs(dx);
}else{
    l=abs(dy);
}


//l = max(abs(dx), abs(dy));



float DX = dx / float(l);
float DY = dy / float(l);

float x=x1;
float y=y1;



glBegin(GL_POINTS);
    for(int i=0;i<=l;i++){
        glColor3i(0,0,0);

        if(LineType==1){
            glVertex2i(round(x),round(y));
            
        }else if(LineType==2){
            
            if(i%5==0){
                glVertex2i(round(x),round(y));

            }

        }else if(LineType==3){
            if(i%10==0){
                glVertex2i(round(x),round(y));

            }
        }
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
    ddaAlgorithm(100,100,200,200,1);
    ddaAlgorithm(-100,-50,-100,-300,2);
    ddaAlgorithm(-300, -450, -100, 500, 3);

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