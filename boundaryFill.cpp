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


void BFill(int x,int y,int fc,int bc){
int ic;
getPixel(x,y,ic);
if((x<0) || (x>=width)) return;
if((y<0) || (y>=height)) return;

if(ic!=fc && ic!=bc){
    glBegin(GL_POINTS);
    glVertex2i(x,y,fc);
    BFill(x+1,y,fc,bc);
    BFill(x-1,y,fc,bc);

    BFill(x,y+1,fc,bc);
    BFill(x,y-1,fc,bc);

    BFill(x+1,y+1,fc,bc);
    BFill(x-1,y-1,fc,bc);
    
    BFill(x-1,y+1,fc,bc);
    BFill(x+1,y-1,fc,bc);
    
}

}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    //ddaAlgorithm(100,100,100,100,1);
    

}



void menu(int index){

}



int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,50);
    glutCreateWindow("DDA Assignment 1");

    glutDisplayFunc(display);
    myInit();
/*
    glutCreateMenu(menu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);*/

    glutMainLoop();
    return 0;

},