#include<GL/glut.h>

int l=1000;
int w=700;

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(5.0);
    gluOrtho2D(0.0,1000.0,0.0,1000.0);
}

void displayline(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);

    glVertex2i(100,100);
    glVertex2i(200,200);

    glEnd();
    glFlush();
}

void displaypoly(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);

    glVertex2i(100,100);
    glVertex2i(200,100);
    glVertex2i(200,200);
    glVertex2i(100,200);
    //glVertex2i(200,200);

    glEnd();
    glFlush();
}

void displayPoints(){
    glClear(GL_COLOR_BUFFER_BIT);       
    glBegin(GL_POINTS)  ;
    int c=100;
    for(int i=0;i<=10;i++){

        c += 20;
        glVertex2i(100,c);

    }

    glEnd();
    glFlush();
    //glVertex2i(101,200);
}

int main(int c,char**v){


    glutInit(&c,v);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(500,100);
    glutInitWindowSize(l,w);
    glutCreateWindow("I am noob");
    init();
    glutDisplayFunc(displayPoints);
    glutMainLoop();
}