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
    glBegin(GL_POINTS);
    for(int i=-wl; i<wl; i++){
        glVertex2i(i, 0);
    }
    for(int i=-wh; i<wh; i++){
        glVertex2i(0, i);
    }
    glEnd();
    glFlush();
}

// Bresenham's Circle Algorithm
void circleAlgo(int r, int h, int k) {

    if(r<1){
        cout<<"Error: Invalid radius";
    }
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
    glPointSize(5.0);
    glColor3f(0.0, 0.129, 0.584);  // Olympic blue
    circleAlgo(100, 100, 300);
    
    glColor3f(1.0, 0.8, 0.0);  // Olympic yellow
    circleAlgo(100, 300, 300);
    
    glColor3f(0.0, 0.0, 0.0);  // Black
    circleAlgo(100, 500, 300);
    
    glColor3f(0.0, 0.6, 0.2);  // Olympic green
    circleAlgo(100, 200, 200);
    
    glColor3f(0.906, 0.082, 0.129);  // Olympic red
    circleAlgo(100, 400, 200);
}

void drawShape() {
    int x = 500;
    int y = -400;
    
    // Draw outer circle
    circleAlgo(200, x, y);
    
    glBegin(GL_LINES);
    
    // First line of triangle
    glVertex2i(500, -200);  // Top point
    glVertex2i(327, -500);  // Bottom left point
    
    // Second line of triangle
    glVertex2i(327, -500);  // Bottom left point
    glVertex2i(673, -500);  // Bottom right point
    
    // Third line of triangle
    glVertex2i(673, -500);  // Bottom right point
    glVertex2i(500, -200);  // Back to top point
    glEnd();
    
    // Draw inner circle
    circleAlgo(80, x, y);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}


void drawSpiral() {
    float angle = 0.0;
    float radius = 5.0;
    float angleIncrement = 0.1;  // Smaller for smoother curves
    float radiusIncrement = 1.5; // Adjusts spacing

    glBegin(GL_LINE_STRIP);  

    while (radius < 300) {  
        int x = -radius * cos(angle) - 700; // Move further left
        int y = radius * sin(angle) + 300;  // Move upward

        glVertex2i(x, y);
        
        angle += angleIncrement;
        radius += radiusIncrement;
    }
    
    glEnd();
    glFlush();
}





void menu(int c) {
   // glClear(GL_COLOR_BUFFER_BIT);
    
    if (c == 1) { // simple circle
        glColor3i(0, 0, 0);
        circleAlgo(100, 0, 0);
    } else if (c == 2) {
        olympicRing();
    } else if (c == 3) {
        glColor3i(0, 0, 0);      
        //concentric circle
        circleAlgo(200, -300, -300); // Outer circle
        circleAlgo(100, -300, -300); // Inner circle
    }else if(c==4){
        glColor3i(0, 0, 0);      
        drawSpiral();
    }
    else if(c==5){
        plotAxis(); //to plot the axis
    }else if(c==6){
        drawShape(); // to draw the shape
    }
    
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

    glutCreateMenu(menu);
    glutAddMenuEntry("Simple circle", 1);
    glutAddMenuEntry("Olympic ring", 2);
    glutAddMenuEntry("Concentric circle", 3);
    glutAddMenuEntry("Spiral", 4);
    glutAddMenuEntry("Draw Axis", 5);
    glutAddMenuEntry("Draw shape", 6);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
