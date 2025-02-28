#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int wl = 1200, wh = 700; // Window size

// Define colors
float borderColor[] = {0.0, 0.0, 0.0};  // Black
float fillColor[] = {1.0, 0.0, 0.0};    // Red

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
    glFlush(); // Ensure previous drawing is completed
    glReadPixels(x + wl, y + wh, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if (!colorEqual(pixel, fc) && !colorEqual(pixel, bc)) {
        glColor3fv(fc);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        // Recursive 4-way filling
        BFill(x + 1, y, fc, bc);
        BFill(x - 1, y, fc, bc);
        BFill(x, y + 1, fc, bc);
        BFill(x, y - 1, fc, bc);
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw square
    glLineWidth(3.0);
    glColor3fv(borderColor);
    glBegin(GL_LINE_LOOP);
    glVertex2i(300, -300);
    glVertex2i(750, -300);
    glVertex2i(750, -700);
    glVertex2i(300, -700);
    glEnd();
    glFlush();

    // Start boundary fill inside the square
    BFill(525, -500, fillColor, borderColor);
}

// Initialization
void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-wl, wl, -wh, wh);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("OpenGL Square with Boundary Fill");

    glutDisplayFunc(display);
    myInit();

    glutMainLoop();
    return 0;
}
