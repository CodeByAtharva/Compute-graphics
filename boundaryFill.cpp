#include <iostream>
#include <GL/glut.h>

using namespace std;

int wl = 600, wh = 500; // Half window size (full window: 1200*1000)

// Define colors
float borderColor[] = {0.0, 0.0, 0.0};  // Black
float fillColor[] = {1.0, 0.0, 0.0};    // Red

// Initialization
void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-wl, wl, -wh, wh);
}

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
        glFlush(); // Ensure immediate

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

    // Draw filled polygon (square)
    glColor3fv(borderColor);
   glBegin(GL_LINES); 

    // Bottom edge
    glVertex2i(250, 200);
    glVertex2i(450, 200);

    // Right edge
    glVertex2i(450, 200);
    glVertex2i(450, 350);

    // Top edge
    glVertex2i(450, 350);
    glVertex2i(250, 350);

    // Left edge
    glVertex2i(250, 350);
    glVertex2i(250, 200);

glEnd();


    glFlush(); // Ensure polygon is drawn before filling

    // Start boundary fill inside the polygon
    BFill(300, 300, fillColor, borderColor);
}


// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl * 2, wh * 2); // Adjusted for proper size
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Boundary Fill Algorithm");

    glutDisplayFunc(display);
    myInit();

    glutMainLoop();
    return 0;
}
