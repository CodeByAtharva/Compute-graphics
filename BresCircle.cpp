#include<iostream>
#include<GL/glut.h>
#include<math.h>

int wl=1400;
int wh=900;
void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    gluOrtho2D(-wl,wl,-wh,wh);

}

void plotAxis(){
    glBegin(GL_LINES);
        glVertex2i(-wl,0); //
        glVertex2i(wl,0);



        glVertex2i(0,-wh);
        glVertex2i(0,wh);

      
    glEnd();
    glFlush();
}



void circleAlgo(int r,int h,int k){

    int d=3-(2*r);
    int x=0;
    int y=r;

    while(x<y){
        if(d<=0){
            d=d+4*x+6;
            x=x+1;
        }else{
            d=d+4*(x-y)+10;
            x=x+1;
            y=y-1;
        }

        glBegin(GL_POINTS);

        glVertex2i(x+h,y+k);
        glVertex2i(-x+h,-y+k);
        
        glVertex2i(y+k,x+h);
        glVertex2i(-y+k,-x+h);
        
        glVertex2i(-y+k,x+h);
        glVertex2i(y+k,-x+h);
        
        glVertex2i(-x+h,y+k);
        glVertex2i(x+h,-y+k);

       
        glEnd();
        glFlush();


    }

}

void olympicRing(){
    circleAlgo(100,200,200);
    circleAlgo(100,300,200);
    //circleAlgo(100,300,400);
    //circleAlgo(100,500,400);
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    //circleAlgo(100,0,0);
    olympicRing();
    plotAxis();
    glFlush();

}

int main(int argc,char** v){
    glutInit(&argc,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,50);
    glutCreateWindow("Bresenhem's Circle Algorithm");

    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
}