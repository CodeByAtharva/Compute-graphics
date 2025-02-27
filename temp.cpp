#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int wl = 1400;
int wh = 900;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3i(0, 0, 0);
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

// Function to plot axis
void plotAxis() {
    glBegin(GL_POINTS);
    for (int i = -wl; i < wl; i++) {
        glVertex2i(i, 0);
    }
    for (int i = -wh; i < wh; i++) {
        glVertex2i(0, i);
    }
    glEnd();
    glFlush();
}

// Bresenham's Circle Algorithm
void circleAlgo(int r, int h, int k) {
    if (r < 1) {
        cout << "Error: Invalid radius\n";
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

// Olympic Rings (shifted downward)
void olympicRing() {
    glPointSize(5.0);
    glColor3f(0.0, 0.129, 0.584);  // Blue
    circleAlgo(100, -200, 150);
    
    glColor3f(1.0, 0.8, 0.0);  // Yellow
    circleAlgo(100, 0, 150);
    
    glColor3f(0.0, 0.0, 0.0);  // Black
    circleAlgo(100, 200, 150);
    
    glColor3f(0.0, 0.6, 0.2);  // Green
    circleAlgo(100, -100, 50);
    
    glColor3f(0.906, 0.082, 0.129);  // Red
    circleAlgo(100, 100, 50);
}

// Shape with modified position
void drawShape() {
    int x = -600; // Shifted left
    int y = -500; // Shifted downward
    
    // Outer Circle
    circleAlgo(200, x, y);
    
    glBegin(GL_LINES);
    
    // Triangle lines
    glVertex2i(x, y + 200);
    glVertex2i(x - 173, y - 100);
    
    glVertex2i(x - 173, y - 100);
    glVertex2i(x + 173, y - 100);
    
    glVertex2i(x + 173, y - 100);
    glVertex2i(x, y + 200);
    
    glEnd();
    
    // Inner Circle
    circleAlgo(80, x, y);
}

// Spiral shifted right
void drawSpiral() {
    float angle = 0.0;
    float radius = 5.0;
    float angleIncrement = 0.1;
    float radiusIncrement = 1.5;

    glBegin(GL_LINE_STRIP);

    while (radius < 300) {  
        int x = radius * cos(angle) + 700; // Shifted right
        int y = radius * sin(angle) - 200; // Shifted downward

        glVertex2i(x, y);
        
        angle += angleIncrement;
        radius += radiusIncrement;
    }
    
    glEnd();
    glFlush();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glFlush();
}

// Concentric Circles 
void concentricCircles() {
    glColor3i(0, 0, 0);
    circleAlgo(200, 700, 300);
    circleAlgo(100, 700, 300);
}

// Menu function
void menu(int c) {
    if (c == 1) { // Simple circle
        glColor3i(0, 0, 0);
        circleAlgo(100, -400, 300);
    } else if (c == 2) {
        olympicRing();
    } else if (c == 3) {
        concentricCircles();
    } else if (c == 4) {
        drawSpiral();
    } else if (c == 5) {
        plotAxis();
    } else if (c == 6) {
        drawShape();
    }
    
    glFlush();
}

int main(int argc, char** v) {
    glutInit(&argc, v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Modified Bresenham's Circle Algorithm");

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
