#include <GL/glut.h>
#include <cmath>

struct Point {
    float x, y;
};

// Function to draw a Koch Curve between two points recursively
void kochCurve(Point a, Point b, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
        glEnd();
        return;
    }

    Point s, t, u;

    // 1/3 point
    s.x = (2 * a.x + b.x) / 3;
    s.y = (2 * a.y + b.y) / 3;

    // 2/3 point
    t.x = (a.x + 2 * b.x) / 3;
    t.y = (a.y + 2 * b.y) / 3;

    // peak of the triangle
    float angle = M_PI / 3; // 60 degrees in radians
    u.x = s.x + (t.x - s.x) * cos(angle) - (t.y - s.y) * sin(angle);
    u.y = s.y + (t.x - s.x) * sin(angle) + (t.y - s.y) * cos(angle);

    // Recursively draw 4 segments
    kochCurve(a, s, depth - 1);
    kochCurve(s, u, depth - 1);
    kochCurve(u, t, depth - 1);
    kochCurve(t, b, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);  // Blue color

    Point a = { -0.9f, 0.0f };
    Point b = { 0.9f, 0.0f };

    int depth = 4; 
    kochCurve(a, b, depth);

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);  // White background
    glColor3f(0, 0, 0);        // Drawing color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1);  // 2D orthographic projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Koch Curve");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
