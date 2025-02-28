#include <iostream>
#include <stack>
#include <GL/glut.h>

using namespace std;

int wl = 1200, wh = 700;  // Window size

// Define colors
float borderColor[] = {0.0, 0.0, 0.0};  // Black
float fillColor[] = {1.0, 0.0, 0.0};    // Red

// Function to check if two colors are equal (with tolerance)
bool colorEqual(unsigned char pixel[], float color[]) {
    return (abs(pixel[0] - (unsigned char)(color[0] * 255)) < 5 &&
            abs(pixel[1] - (unsigned char)(color[1] * 255)) < 5 &&
            abs(pixel[2] - (unsigned char)(color[2] * 255)) < 5);
}

// Stack-based Flood Fill (avoiding stack overflow)
void BFill(int x, int y, float fc[], float bc[]) {
    stack<pair<int, int>> pixelStack;
    pixelStack.push({x, y});

    while (!pixelStack.empty()) {
        auto [px, py] = pixelStack.top();
        pixelStack.pop();

        // Convert world coordinates to screen coordinates
        int sx = px + wl;  // Convert from (-wl, wl) to (0, 2*wl)
        int sy = py + wh;  // Convert from (-wh, wh) to (0, 2*wh)

        // Read pixel color
        unsigned char pixel[3];
        glReadPixels(sx, sy, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

        // If pixel is already filled or it's a border, continue
        if (colorEqual(pixel, fc) || colorEqual(pixel, bc)) {
            continue;
        }

        // Fill the pixel
        glColor3fv(fc);
        glBegin(GL_POINTS);
        glVertex2i(px, py);
        glEnd();
        glFlush();

        // Push adjacent pixels
        pixelStack.push({px + 1, py});
        pixelStack.push({px - 1, py});
        pixelStack.push({px, py + 1});
        pixelStack.push({px, py - 1});
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
