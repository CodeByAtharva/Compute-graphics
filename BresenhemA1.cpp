#include <iostream>
#include <GL/glut.h>
#include<math.h>


int wl=1400;
int wh=900;

void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    gluOrtho2D(-wl,wl,-wh,wh);

}

int sign(int val){
    if(val<0){
        return -1;
    }else if(val==0){
        return 0;
    }else{
        return 1;
    }
}

void BAlgorihtm(int x1,int y1,int x2,int y2,int LineType){
    int x=x1;
    int y=y1;
    int Dx=abs(x2-x1);
    int Dy=abs(y2-y1);
    int s1=sign(x2-x1);
    int s2=sign(y2-y1);
    int interchange;

    if(Dy>Dx){
        int temp=Dx;
        Dx=Dy;
        Dy=temp;
        interchange=1;
    }else{
        interchange=0;
    }

    int e=2*Dy-Dx;

    glBegin(GL_POINTS);
       // glVertex2i(x,y);

        for(int i=1;i<=Dx;i++){
           // glVertex2i(x,y);

            if (LineType == 1) {  // Solid line
                glVertex2i(x, y);
            } else if (LineType == 2) {  //dashed line
                if (i % 5 ==0) {  
                    glVertex2i(x, y);
                }
            } else if (LineType == 3) {  //dotted line
                if (i % 10 == 0) {  
                    glVertex2i(x, y);
                }
            }






            while(e>=0){
                if(interchange==1){
                    x=x+s1;
                }else{
                    y=y+s2;
                }
                e=e-2*Dx;
            }

            if(interchange==1){
                y=y+s2;
            }else{
                x=x+s1;
            }
            e=e+2*Dy;


        }
        glEnd();
        glFlush();

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    BAlgorihtm(-wl,0,wl,0,1);
    BAlgorihtm(0,-wh,0,wh,1);

    BAlgorihtm(100,100,200,200,1); //simple line
    BAlgorihtm(-100,-50,-100,-300,2); //dashed line
    BAlgorihtm(-300, -450, -100, 500, 3); //dotted line

}

int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,50);
    glutCreateWindow("DDA Assignment 1");

    glutDisplayFunc(display);
    myInit();



    glutMainLoop();
    return 0;

}