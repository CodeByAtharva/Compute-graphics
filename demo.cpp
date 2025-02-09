#include <iostream>
#include <GL/glut.h>

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glColor3f(0.0f, 0.0f, 0.0f);     
    glPointSize(4.0);   
    glMatrixMode(GL_PROJECTION);      
    glLoadIdentity();                 
    gluOrtho2D(0.0, 640.0, 0.0, 480.0); 
}


void MyDisplay3(void) {
    glClear(GL_COLOR_BUFFER_BIT);    
    glBegin(GL_LINES);
    
    glVertex2i(100, 50);              
    glVertex2i(100, 300);
    
    glVertex2i(100, 300);
    glVertex2i(300, 300);
    
                  
    glVertex2i(300, 300);
    glVertex2i(300, 240);   
    
    glVertex2i(300, 240);
    glVertex2i(160, 240); 
    
    glVertex2i(160, 240); 
    glVertex2i(160, 180); 
    
    glVertex2i(160, 180); 
    glVertex2i(220, 180); 
        
     glVertex2i(220, 180); 
     glVertex2i(220, 120); 
     
     
    glVertex2i(220, 120); 
    glVertex2i(160, 120);
    
    
     glVertex2i(160, 120);
      glVertex2i(160, 50);
      
         glVertex2i(160, 50);
            glVertex2i(100, 50);
   
    glEnd();
    glFlush();                     
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);   
    glutInitWindowPosition(100, 150); 
    glutCreateWindow("My Last Attempt"); 
     
    glutDisplayFunc(MyDisplay3);     
    myInit();                         
    glutMainLoop();                 
    return 0;
}