#include <iostream>
#include <GL/glut.h>

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glColor3f(0.0f, 0.0f, 0.0f);     

    gluOrtho2D(0.0, 700.0, 0.0, 500.0); 
}

void MyDisplay3(void) {
    glClear(GL_COLOR_BUFFER_BIT);    

    glBegin(GL_LINES);
    
    // House base
    glVertex2i(250, 200); // Bottom-left
    glVertex2i(450, 200); // Bottom-right

    glVertex2i(450, 200); // Bottom-right
    glVertex2i(450, 350); // Top-right

    glVertex2i(450, 350); // Top-right
    glVertex2i(250, 350); // Top-left

    glVertex2i(250, 350); // Top-left
    glVertex2i(250, 200); // Bottom-left

    // Roof
    glVertex2i(250, 350); // Left corner
    glVertex2i(450, 350); // Right corner

    glVertex2i(250, 350); // Left corner
    glVertex2i(350, 450); // Top center

    glVertex2i(350, 450); // Top center
    glVertex2i(450, 350); // Right corner

    // Door
    glVertex2i(320, 200); // Bottom-left
    glVertex2i(380, 200); // Bottom-right

    glVertex2i(380, 200); // Bottom-right
    glVertex2i(380, 280); // Top-right

    glVertex2i(380, 280); // Top-right
    glVertex2i(320, 280); // Top-left

    glVertex2i(320, 280); // Top-left
    glVertex2i(320, 200); // Bottom-left

    glEnd();
    glFlush();                     
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 550);   
    glutInitWindowPosition(100, 150); 
    glutCreateWindow("Simple House Drawing"); 
     
    glutDisplayFunc(MyDisplay3);     
    myInit();                         
    glutMainLoop();                 
    return 0;
}
