#include<iostream>
#include<GL/glut.h>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define w 800
#define h 800

struct Point{
    float x,y;
};

vector<Point> polygon,clippedPolygon;
Point windowMin,windowMax;

int currentMode=0,windowClick=0;

Point intersection(Point p1,Point p2,int edge){
    Point i;
    float m=(p2.y-p1.y)/(p2.x-p1.x+0.00001);

    switch(edge){
        case 0: i.x=windowMin.x;
                i.y=p1.y+m*(windowMin.x-p1.x);
                break;
        case 1: i.x=windowMax.x;
                i.y=p1.y+m*(windowMax.x-p1.x);
                break;
        case 2: i.y=windowMin.y;
                i.x=p1.x+(windowMin.y-p1.y)/m;
                break;
        case 3: i.y=windowMax.y;
                i.x=p1.x+(windowMax.y-p1.y)/m;
                break;
    }
    return i;
}

bool isInside(Point p,int edge){
    switch(edge){
        case 0: return (p.x>=windowMin.x);
        case 1: return (p.x<=windowMax.x);
        case 2: return (p.y>=windowMin.y);
        case 3: return (p.y<=windowMax.y);
    }
    return false;
}
vector<Point> sh(vector<Point> input,int edge){
    vector<Point> output;
    Point S=input.back();

    for(auto E:input){
        if(isInside(E,edge)){
            if(isInside(S,edge)){
                output.push_back(E);
            }
            else{
                output.push_back(intersection(S,E,edge));
                output.push_back(E);
            }
        }
        else if(isInside(S,edge)){
            output.push_back(intersection(S,E,edge));
        }
        S=E;
    }
    return output;
}

void clipPolygon(){
    clippedPolygon=polygon;
    for(int edge=0;edge<4;edge++){
        clippedPolygon=sh(clippedPolygon,edge);
    }
}
void mouseClick(int button,int state,int x,int y){
    if(state==GLUT_DOWN){
        float X=(x-w/2.0f)*2.0f;
        float Y=(h/2.0f-y)*2.0f;
        Point clickPoint={X,Y};

        if(currentMode==1){
            if(windowClick==0){
                windowMin=clickPoint;
                windowClick++;
            }
            else{
                windowMax=clickPoint;
                if(windowMin.x>windowMax.x){
                    swap(windowMin.x,windowMax.x);
                }
                if(windowMin.y>windowMax.y){
                    swap(windowMin.y,windowMax.y);
                }

                windowClick=0;
            }
        }

        else if(currentMode==2){
            polygon.push_back(clickPoint);
        }
    }
    glutPostRedisplay();
}
void menu(int index){
    currentMode=index;

    if(index==3){
        clippedPolygon.clear();
        clipPolygon();
    }

    glutPostRedisplay();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(-w,0);
    glVertex2f(w,0);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(windowMin.x,windowMin.y);
    glVertex2f(windowMin.x,windowMax.y);
    glVertex2f(windowMax.x,windowMax.y);
    glVertex2f(windowMax.x,windowMin.y);
    glEnd();

    if(!polygon.empty())
    {
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
        for(auto p:polygon){
            glVertex2f(p.x,p.y);
        }
        glEnd();
    }

    float offset=800;

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(windowMin.x,windowMin.y-offset);
    glVertex2f(windowMin.x,windowMax.y-offset);
    glVertex2f(windowMax.x,windowMax.y-offset);
    glVertex2f(windowMax.x,windowMin.y-offset);
    glEnd();

    if(!clippedPolygon.empty()){
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINE_LOOP);
        for(auto p:clippedPolygon){
            glVertex2f(p.x,p.y-offset);
        }
        glEnd();
    }
    glFlush();
}
void init(){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-w,w,-h,h);
}
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(w,h);
    glutInitWindowPosition(100,100);
    glutCreateWindow("polygon clipping algorithm");

    glutCreateMenu(menu);
    glutAddMenuEntry("draw window",1);
    glutAddMenuEntry("draw polygon",2);
    glutAddMenuEntry("clip polygon",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMainLoop();

    return 0;
}
