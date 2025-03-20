#include <iostream>
#include <GL/glut.h>

#define wl 1200
#define wh 700

float fillColor[3] = {0, 0, 0}, readpixel[3];
int X, Y;

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

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, wl, 0, wh);
}

void floodfill(int x, int y) {
    getpixel(x, y, readpixel);
    if (readpixel[0] == 1.0 && readpixel[1] == 1.0 && readpixel[2] == 1.0) { // Check if it's the white background
        setpixel(x, y);
        floodfill(x + 1, y);
        floodfill(x, y + 1);
        floodfill(x - 1, y);
        floodfill(x, y - 1);
        glEnd();
        glFlush();
    }
}

void drawSquare() {
    glColor3f(0.0f, 0.0f, 0.0f);
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

void create_menu(int item) {
    if (item == 1) {
        drawSquare();
    }
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        X = x;
        Y = wh - y;
        floodfill(X, Y);
    }
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 150);

    glutCreateWindow("Simple Square with GL_LINES");
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouseClick);
    glutCreateMenu(create_menu);
    glutAddMenuEntry("DRAW SQUARE", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    myInit();
    glutMainLoop();
    return 0;
}
