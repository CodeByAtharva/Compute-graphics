#include <iostream>
#include <GL/glut.h>

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glColor3f(0.0f, 0.0f, 0.0f);     

//    gluOrtho2D(left, right, bottom, top);
    gluOrtho2D(0.0, 700.0, 0.0, 500.0); 
}


void MyDisplay3(void) {
    glClear(GL_COLOR_BUFFER_BIT);    
    glBegin(GL_LINES);
    
    
   
    glEnd();
    glFlush();                     
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);   
    glutInitWindowPosition(100, 150); 
    glutCreateWindow("My First Attempt"); 
     
    glutDisplayFunc(MyDisplay3);     
    myInit();                         
    glutMainLoop();                 
    return 0;
}