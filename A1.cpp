#include<iostream>
#include<GL/glut.h>
#include<cmath>

using namespace std;
#define wl 1200
#define wh 700
void myInit(){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    gluOrtho2D(-wl,wl,-wh,wh);
}

void dda(int x1,int y1,int x2,int y2,int line){
    if(x1==x2 && y1==y2){
        cout<<"Error: source and destination are same";
        return;
    }

    int dx=x2-x1;
    int dy=y2-y1;

    int len;

    if(abs(dx)>abs(dy)){
        len=abs(dx);
    }else{
        len=abs(dy);
    }

    float xinc=dx/float(len);
    float yinc=dy/float(len);

    float x=x1;
    float y=y1;

    //glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for(int i=0;i<=len;i++){
        if(line==1){
            glVertex2i(round(x),round(y));
        }else if(line==2){
            if(i%5==0){
                glVertex2i(round(x),round(y));
            }
        }else if(line==3){
            if(i%10==0){
                glVertex2i(round(x),round(y));
            }
        }else if(line==4){


            int patlen=20;
            int dash=5;
            int dot=12;
            int mod=i%patlen;
            if(mod<dash || mod==dot){
                glVertex2i(round(x),round(y));
            }

        }
        x=x+xinc;
        y=y+yinc;
    }
    glEnd();
    glFlush();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    dda(-wl,0,wl,0,1);
    dda(0,-wh,0,wh,1);
   // dda(0,0,100,0);
    //dda(0,0,0,0);
    //glFlush();
}

void menu(int i){
    switch(i){
        case 1:
        dda(-200,-300,300,500,1);
        break;

        case 2:
        dda(300,-500,100,0,2);
        break;

        case 3:
        dda(-500, 300, 400, -200, 3);
        break;

        case 4:
        dda(-300,-200,-500,-400,4);
        break;

        case 5:
        glClear(GL_COLOR_BUFFER_BIT);
        break;

    }
}

int main(int c,char** v){
    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,200);
    glutCreateWindow("DDA Line");
    myInit();
    glutDisplayFunc(display);

    glutCreateMenu(menu);
    glutAddMenuEntry("Simple line",1);
    glutAddMenuEntry("dashed",2);
    glutAddMenuEntry("doted",3);
    glutAddMenuEntry("dashed-doted",4);
    glutAddMenuEntry("Clear",5);
    //glutAddMenuEntry("");
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}