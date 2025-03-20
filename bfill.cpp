#include <iostream>
#include <GL/glut.h>

#define w 1200
#define h 700
#define wl w/2  // Half width
#define wh h/2  // Half height

float fillColor[3] = {0, 0, 1};  // Blue fill color
float boundaryColor[3] = {0, 0, 0};  // Black boundary color

// Function to check if two colors are equal
bool colorEqual(unsigned char pixel[], float color[]) {
    return (pixel[0] == (unsigned char)(color[0] * 255) &&
            pixel[1] == (unsigned char)(color[1] * 255) &&
            pixel[2] == (unsigned char)(color[2] * 255));
}

// Boundary Fill Algorithm
void BFill(int x, int y, float fc[], float bc[]) {
    if (x < -wl || x >= wl || y < -wh || y >= wh) return; // Boundary check
    
    unsigned char pixel[3];
    glReadPixels(x + wl, y + wh, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if (!colorEqual(pixel, fc) && !colorEqual(pixel, bc)) {
        glColor3fv(fc);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush(); // Ensure immediate effect

        // Recursive 4-way filling
        BFill(x + 1, y, fc, bc);
        BFill(x - 1, y, fc, bc);
        BFill(x, y + 1, fc, bc);
        BFill(x, y - 1, fc, bc);
    }
}

// Function to draw the square using GL_LINES
void drawSquare() {
    glColor3fv(boundaryColor);
    glBegin(GL_LINES);

    glVertex2f(250, 250);
    glVertex2f(350, 250);

    glVertex2f(350, 250);
    glVertex2f(350, 350);

    glVertex2f(350, 350);
    glVertex2f(250, 350);

    glVertex2f(250, 350);
    glVertex2f(250, 250);

    glEnd();
    glFlush();
}

// Mouse callback for filling the square
void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        int X = x;
        int Y = h - y; // Convert to OpenGL coordinate system
        BFill(X, Y, fillColor, boundaryColor);
    }
}

// Initialization
void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

// Display function
void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare(); // Automatically draw the square
    glFlush();
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 150);

    glutCreateWindow("Boundary Fill Algorithm");
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouseClick);

    myInit();
    glutMainLoop();
    return 0;
}
