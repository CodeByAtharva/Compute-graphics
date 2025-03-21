
#include <GL/glut.h>
#include <iostream>
#define w 640
#define h 480
using namespace std;

float boundaryColor[3] = {1, 0, 0}, interiorColor[3] = {1, 1, 1}, fillColor[3] = {0, 0, 0}, readpixel[3];
bool fillalgo = true;

void setpixel(int x, int y) {
    glColor3fv(fillColor);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void getpixel(int x, int y, float *color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

// Recursive boundary fill algorithm
void boundaryFill(int x, int y) {
    if (x >= w || x < 0 || y >= h || y < 0) return; // Boundary check

    getpixel(x, y, readpixel);
    if ((readpixel[0] != boundaryColor[0] || readpixel[1] != boundaryColor[1] || readpixel[2] != boundaryColor[2]) &&
        (readpixel[0] != fillColor[0] || readpixel[1] != fillColor[1] || readpixel[2] != fillColor[2])) {
        setpixel(x, y);

        // Recursively call for neighboring pixels
        boundaryFill(x + 1, y);
        boundaryFill(x - 1, y);
        boundaryFill(x, y + 1);
        boundaryFill(x, y - 1);
    }
}

// Recursive flood fill algorithm
void floodfill(int x, int y) {
    if (x >= w || x < 0 || y >= h || y < 0) return; // Boundary check

    getpixel(x, y, readpixel);
    if (readpixel[0] == interiorColor[0] && readpixel[1] == interiorColor[1] && readpixel[2] == interiorColor[2]) {
        setpixel(x, y);

        // Recursively call for neighboring pixels
        floodfill(x + 1, y);
        floodfill(x - 1, y);
        floodfill(x, y + 1);
        floodfill(x, y - 1);
    }
}

void drawHollowRectangle(int x1, int y1, int x2, int y2) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        int X = x;
        int Y = h - y; // Adjust for OpenGL coordinate system

        if (fillalgo) {
            floodfill(X, Y);
        } else {
            boundaryFill(X, Y);
        }
    }
}

void menu(int index) {
    if (index == 1) {
        fillalgo = true;
    } else if (index == 2) {
        fillalgo = false;
    } else if (index == 3) {
        exit(0);
    }

    // Clear screen and redraw the rectangle
    glClear(GL_COLOR_BUFFER_BIT);
    drawHollowRectangle(100, 100, 250, 250);
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawHollowRectangle(100, 100, 250, 250);
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glColor3f(1.0, 0.0, 0.0);         // Set default drawing color to red
    glMatrixMode(GL_PROJECTION);      // Set projection mode
    glLoadIdentity();                 // Reset projection matrix
    gluOrtho2D(0, w, 0, h);           // Set orthographic projection
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);                              // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);        // Set display mode
    glutInitWindowSize(w, h);                           // Set window size
    glutInitWindowPosition(100, 150);                   // Set window position
    glutCreateWindow("Seed Fill Algorithm with Recursion"); // Create window

    glutCreateMenu(menu);                               // Create menu
    glutAddMenuEntry("Flood Fill", 1);                  // Add menu entries
    glutAddMenuEntry("Boundary Fill", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);                  // Attach menu to right button

    init();                                             // Initialize OpenGL settings
    glutDisplayFunc(display);                           // Set display callback
    glutMouseFunc(mouseClick);                          // Set mouse callback
    glutMainLoop();                                     // Enter main loop

    return 0;
}

