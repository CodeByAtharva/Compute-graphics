#include <iostream>
#include <GL/glut.h>
#include <math.h>

int wl = 1400;
int wh = 900;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3i(0, 0, 0);
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}


//function to plot axis
void plotAxis(){
    for(int i=-wl;i<wl;i++){
        glBegin(GL_POINTS);
        glVertex2i(i,0);
        glEnd();
    }
    for(int i=-wh;i<wh;i++){
        glBegin(GL_POINTS);
        glVertex2i(0,i);
        glEnd();
    }
    glFlush();
}

// Bresenham's Circle Algorithm
void circleAlgo(int r, int h, int k) {
    int d = 3 - (2 * r);
    int x = 0;
    int y = r;

    glBegin(GL_POINTS);
    while (x <= y) {  
        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;  
        }
        x++;
        
        
        // Plot all 8 symmetrical points
        glVertex2i(h + x, k + y);
        glVertex2i(h - x, k + y);
        glVertex2i(h + x, k - y);
        glVertex2i(h - x, k - y);
        
        glVertex2i(h + y, k + x);
        glVertex2i(h - y, k + x);
        glVertex2i(h + y, k - x);
        glVertex2i(h - y, k - x);

    }
    glEnd();
    glFlush();
}

void olympicRing() {

    circleAlgo(100, 200, 200);
    circleAlgo(100, 400, 200);
    circleAlgo(100, 300, 300);
    circleAlgo(100, 500, 300);
    circleAlgo(100, 100, 300);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    olympicRing();
    plotAxis();
    glFlush();
}

int main(int argc, char** v) {
    glutInit(&argc, v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Bresenham's Circle Algorithm");

    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;
}
