#include <iostream>
#include <GL/glut.h>
#include<math.h>

using namespace std;


int wl=1200;
int wh=700;
void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3i(0,0,0);
    glPointSize(2.0);
    gluOrtho2D(-wl,wl,-wh,wh);

}


void ddaAlgorithm(int x1,int y1,int x2,int y2, int LineType){

    //validation for checking source and destination points
    if (x1 == x2 && y1 == y2) {
        cout << "Error: Source and Destination points are the same! Line cannot be drawn." << endl;
        return;
    }


int l;  
int dx=x2-x1;
int dy=y2-y1;

//to find out the length

if(abs(dx)>abs(dy)){
    l=abs(dx);
}else{
    l=abs(dy);
}



float DX = dx / float(l);
float DY = dy / float(l);

float x=x1;
float y=y1;


glBegin(GL_POINTS);
    for(int i=0;i<=l;i++){
        glColor3i(0,0,0);

        if(LineType==1){ //simple
            glVertex2i(round(x),round(y));
            
        }else if(LineType==2){ //dashed
            
            if(i%5==0){
                glVertex2i(round(x),round(y));

            }

        }else if(LineType==3){ //dotted
            if(i%10==0){
                glVertex2i(round(x),round(y));

            }
        }else if(LineType==4){ // dashed-dotted
            int patternLength = 20;
            int dashLength = 5;
            int dotPosition = 12;
        
            int mod = i % patternLength;
            if(mod < dashLength || mod == dotPosition){
                glVertex2i(round(x), round(y));
            }
        }
        x=x+DX;
        y=y+DY;
    }

    glEnd();
    glFlush();


}




void drawBoat(){
    ddaAlgorithm(300,-300,750,-300,1); //horizotal big 1
    ddaAlgorithm(300,-350,750,-350,1); //horizotal big 2
    ddaAlgorithm(400,-500,650,-500,1); //horizontal short
    
    ddaAlgorithm(300,-300,300,-350,1); //joint the vertical left part 
    ddaAlgorithm(750,-350,750,-300,1); //joint the vertical right part 
    

    ddaAlgorithm(400,-500,300,-350,1); //connecting left sides
    ddaAlgorithm(650,-500,750,-350,1); //horizontal right sides

    ddaAlgorithm(500,-50,550,-50,1); //top of the stick
    ddaAlgorithm(500,-50,500,-300,1); //left part of the stick
    ddaAlgorithm(550,-50,550,-300,1); //right part of the stick
    
    //ddaAlgorithm(450,-150,600,-150,1); //horizotal flage bottom
    
    //thread part of the flag
    ddaAlgorithm(550,-75,575,-75,1); //top 
    ddaAlgorithm(550,-200,575,-200,1); //bottom
    
    
    //flag
    ddaAlgorithm(575,-50,575,-250,1); //left
    ddaAlgorithm(575,-250,675,-150,1); //bottom-top line
    ddaAlgorithm(575,-50,675,-150,1); //top-bottom line



}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    //ddaAlgorithm(100,100,100,100,1);

}



void menu(int index){
    
    if(index==1){
        ddaAlgorithm(100,100,200,200,1); //simple line
        
    }else if(index==2){
        ddaAlgorithm(-100,-50,-100,-300,2); //dashed line

    }else if(index==3){
        ddaAlgorithm(-300, -450, -100, 500, 3); //dotted line
    }else if(index==4){
        ddaAlgorithm(-50, -350, -50, 400, 4); //dashed dotted line
    }else if(index==5){
        drawBoat();
    }
    else if(index==6){ //draw axis
        ddaAlgorithm(-wl,0,wl,0,1);
        ddaAlgorithm(0,-wh,0,wh,1);
    }

}



int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,50);
    glutCreateWindow("DDA Assignment 1");

    glutDisplayFunc(display);
    myInit();

    glutCreateMenu(menu);

    glutAddMenuEntry("simple line",1);
    glutAddMenuEntry("dashed line",2);
    glutAddMenuEntry("dotted line",3);
    glutAddMenuEntry("dashed dotted line",4);
    glutAddMenuEntry("boat",5);
    glutAddMenuEntry("draw Axis",6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;

}