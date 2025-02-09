#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>  // Add this line


using namespace std;

struct Point {
    int x, y;
};

vector<Point> points;
int lineType = 0; // 0: Simple, 1: Dotted, 2: Dashed, 3: Solid

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawDDA(Point p1, Point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = max(abs(dx), abs(dy));
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = p1.x, y = p1.y;
    
    for (int i = 0; i <= steps; i++) {
        if (lineType == 0 || (lineType == 1 && i % 5 == 0) || (lineType == 2 && i % 10 < 5) || lineType == 3) {
            setPixel(round(x), round(y));
        }
        x += xInc;
        y += yInc;
    }
}

void drawBresenham(Point p1, Point p2) {
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    int err = dx - dy;
    int count = 0;

    while (true) {
        if (lineType == 0 || (lineType == 1 && count % 5 == 0) || (lineType == 2 && count % 10 < 5) || lineType == 3) {
            setPixel(p1.x, p1.y);
        }
        if (p1.x == p2.x && p1.y == p2.y) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; p1.x += sx; }
        if (e2 < dx) { err += dx; p1.y += sy; }
        count++;
    }
}

void drawAxis() {
    glColor3f(1, 1, 1);
    drawDDA({-400, 0}, {400, 0}); // X-axis
    drawDDA({0, -400}, {0, 400}); // Y-axis
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    glColor3f(0, 1, 0);
    if (points.size() == 2) {
        drawDDA(points[0], points[1]);
        drawBresenham(points[0], points[1]);
    }
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int wx = x - 400;
        int wy = 400 - y;
        points.push_back({wx, wy});
        if (points.size() == 2) glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int, int) {
    if (key == '1') lineType = 0;
    if (key == '2') lineType = 1;
    if (key == '3') lineType = 2;
    if (key == '4') lineType = 3;
    if (key == 'c') points.clear();
    glutPostRedisplay();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Line Drawing Algorithms");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
