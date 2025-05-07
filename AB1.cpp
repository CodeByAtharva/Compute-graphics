#include<iostream>
#include<GL/glut.h>
#include<cmath>

#define wl 1200
#define wh 700

void myInit(){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    gluOrtho2D(-wl,wl,-wh,wh);
}


int sign(int i){
    if(i<0)return -1;
    else if(i==0)return 0;
    else return 1;
}

void bline(int x1,int y1,int x2,int y2,int line){

    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    int s1=sign(x2-x1);
    int s2=sign(y2-y1);

    int change;
    if(dy>dx){
        int temp=dx;
        dx=dy;
        dy=temp;
        change=1;
    }else{
        change=0;
    }

    int e=2*dx-dy;
    int x=x1;
    int y=y1;

    glBegin(GL_POINTS);
    for(int i=0;i<=dx;i++){
        if(line==1){
            glVertex2i(x,y);
        }else if(line==2){
            int patlen=20;
            int dash=12;
            int dot=5;
            int mod=i%patlen;

            if(mod<dash || mod==dot){
                glVertex2i(x,y);
            }
        }
        while(e>=0){
            if(change==1){
                x=x+s1;
            }else{
                y=y+s2;
            }
            e=e-2*dy;
        }
        if(change==1){
            y=y+s2;
        }else{
            x=x+s1;
        }
        e=e+2*dy;
    }
    glEnd();
    glFlush();

}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    bline(-wl,0,wl,0,1);
    bline(0,-wh,0,wh,1);
    bline(0,0,0,400,2);
    glFlush();
}

void menu(int i){
    switch(i){
        case 1:
        bline(100,200,-300,-400,1);
        break;

        case 2:
        bline(0,0,0,400,2);
        break;
    }
    glutPostRedisplay();
}

int main(int c,char** v){
    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,200);

    glutCreateWindow("Bresenhem Line");
    myInit();
    glutDisplayFunc(display);

    glutCreateMenu(menu);
    glutAddMenuEntry("simple line",1);
    glutAddMenuEntry("dasshed-dotted",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;

}