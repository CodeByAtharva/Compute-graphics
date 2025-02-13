
#include <GL/glut.h>
#include<cmath>
#include <iostream>
using namespace std;
void myInit(void){
glClearColor(1.0,1.0,1.0,1.0);
glColor3f(0.0f,0.0f,0.0f);
glPointSize(2.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-320.0,320.0,-240.0,240.0);
}
float sign(float x){
if(x<0){
return-1;
}
else if(x==0){
return 1;
}
else{
return 1;
}
}
void ddaLine(int x1, int y1, int x2, int y2) {
    if(x1==x2&&y1==y2){
    glBegin(GL_POINTS);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
    cout<<"Error - Origin and Destination are same"<<endl;
    return;

}
int dx = x2 - x1;
int dy = y2 - y1;
int length;
if(abs(dx)>abs(dy)){
length=dx;
}
else{
length=dy;
}
float DX = dx / float(length);
float DY = dy / float(length);
float x = x1;
float y = y1;

sign(DX);
sign(DY);
glBegin(GL_POINTS);
int counter = 0;
for (int i = 0; i <= length; i++) {
    
       glColor3f(0.0, 0.0, 0.0);    
       glVertex2i(round(x), round(y));
      

  
x +=(DX);
y +=(DY);
}
glEnd();
glFlush();
}

void plotAxis(){
    ddaLine(-320,0,320,0);
    ddaLine(0,-240,0,240);
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
ddaLine(200, 150, 320, 150);
plotAxis();
glutSwapBuffers();
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(640, 480);
glutCreateWindow("DDA Line Drawing");
myInit();
glutDisplayFunc(display);
glutMainLoop();
return 0;
}