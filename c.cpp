#include <GL/glut.h>
#include <algorithm>
using namespace std;

const int MAX_POINTS = 100;

struct Point {
    float x, y;
};

Point polygon[MAX_POINTS];
Point clippedPolygon[MAX_POINTS];
int polyCount = 0;
int clippedCount = 0;

Point winMin, winMax;
bool selectingWindow = true;
bool windowDefined = false;
int clickCount = 0;

int windowWidth = 800, windowHeight = 600;

// Draw rectangle
void drawRect(Point p1, Point p2) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);
    glEnd();
}

// Inside test
bool inside(Point p, int edge) {
    switch (edge) {
        case 0: return p.x >= winMin.x; // Left
        case 1: return p.x <= winMax.x; // Right
        case 2: return p.y >= winMin.y; // Bottom
        case 3: return p.y <= winMax.y; // Top
    }
    return false;
}

// Compute intersection point
Point intersect(Point p1, Point p2, int edge) {
    Point i;
    float m = 0.0f;
    if (p1.x != p2.x)
        m = (p2.y - p1.y) / (p2.x - p1.x);

    switch (edge) {
        case 0:
            i.x = winMin.x;
            i.y = p1.y + m * (winMin.x - p1.x);
            break;
        case 1:
            i.x = winMax.x;
            i.y = p1.y + m * (winMax.x - p1.x);
            break;
        case 2:
            i.y = winMin.y;
            if (p1.x == p2.x) i.x = p1.x;
            else i.x = p1.x + (winMin.y - p1.y) / m;
            break;
        case 3:
            i.y = winMax.y;
            if (p1.x == p2.x) i.x = p1.x;
            else i.x = p1.x + (winMax.y - p1.y) / m;
            break;
    }
    return i;
}

// Sutherland-Hodgman algorithm
void clipPolygon() {
    Point input[MAX_POINTS];
    int inputCount = polyCount;

    for (int i = 0; i < polyCount; i++)
        input[i] = polygon[i];

    for (int edge = 0; edge < 4; edge++) {
        Point output[MAX_POINTS];
        int outCount = 0;

        for (int i = 0; i < inputCount; i++) {
            Point curr = input[i];
            Point prev = input[(i + inputCount - 1) % inputCount];
            bool currIn = inside(curr, edge);
            bool prevIn = inside(prev, edge);

            if (prevIn && currIn) {
                output[outCount++] = curr;
            } else if (prevIn && !currIn) {
                output[outCount++] = intersect(prev, curr, edge);
            } else if (!prevIn && currIn) {
                output[outCount++] = intersect(prev, curr, edge);
                output[outCount++] = curr;
            }
        }

        for (int i = 0; i < outCount; i++)
            input[i] = output[i];
        inputCount = outCount;
    }

    clippedCount = inputCount;
    for (int i = 0; i < clippedCount; i++)
        clippedPolygon[i] = input[i];
}

// Normalize y coordinate
float normalizeY(int y) {
    return (windowHeight - y) / (float)windowHeight * 2.0f - 1.0f;
}

// Mouse handling
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        float fx = (float)x / windowWidth * 2.0f - 1.0f;
        float fy = normalizeY(y);

        if (fy < 0.0f) return;

        if (selectingWindow) {
            if (clickCount == 0) {
                winMin = {fx, fy};
                clickCount++;
            } else {
                winMax = {fx, fy};
                if (winMin.x > winMax.x) std::swap(winMin.x, winMax.x);
                if (winMin.y > winMax.y) std::swap(winMin.y, winMax.y);
                selectingWindow = false;
                windowDefined = true;
                clickCount = 0;
            }
        } else {
            if (polyCount < MAX_POINTS) {
                polygon[polyCount++] = {fx, fy};
            }
        }
    } else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
        if (windowDefined && polyCount > 0) {
            clipPolygon();
        }
    }

    glutPostRedisplay();
}

// Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw original window
    if (windowDefined) {
        glColor3f(0.0f, 0.0f, 0.0f);
        drawRect(winMin, winMax);
    }

    // Draw polygon
    if (polyCount > 0) {
        glColor3f(0.2f, 0.5f, 0.9f);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < polyCount; i++)
            glVertex2f(polygon[i].x, polygon[i].y);
        glEnd();
    }

    // Draw clipped polygon in bottom half
    if (clippedCount > 0 && windowDefined) {
        float dy = -1.0f;
        Point shiftedMin = {winMin.x, winMin.y + dy};
        Point shiftedMax = {winMax.x, winMax.y + dy};

        glColor3f(0.0f, 0.0f, 0.0f);
        drawRect(shiftedMin, shiftedMax);

        glColor3f(1.0f, 0.2f, 0.2f);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < clippedCount; i++)
            glVertex2f(clippedPolygon[i].x, clippedPolygon[i].y + dy);
        glEnd();
    }

    // Draw horizontal dividing line
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

// Init OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
    glutCreateWindow("Polygon Clipping ");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}