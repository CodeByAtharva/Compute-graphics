#include<GL/glut.h>

void d(){

}

int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(550,200);
    glutInitWindowSize(1000,500);

    glutCreateWindow("title");
    glutDisplayFunc(d);

    glutMainLoop();




}