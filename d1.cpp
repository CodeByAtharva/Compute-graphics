#include<GL/glut.h>


void init()
{
    glClearColor(1.0,0.0,0.0,1.0);
    glColor3i(0,1,0);
    gluOrtho2D(0.0,500.0,0.0,500.0);
}

void d(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);

    glVertex2i(100,100);
    glVertex2i(200,200);

    glEnd();
    glFlush();
}

int main(int c,char**v){


    glutInit(&c,v);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(500,500);
    glutInitWindowSize(500,500);
    glutCreateWindow("I am noob");
    init();
    glutDisplayFunc(d);
    glutMainLoop();
}