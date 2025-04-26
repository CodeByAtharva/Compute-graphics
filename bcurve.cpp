#include <iostream>
#include <GL/glut.h>
#include <math.h>

int cp[4][2] = {{50, 400}, {150, 450}, {300, 50}, {500, 300}};
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void ControlPoints()
{
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; i++) {
        glVertex2f(cp[i][0], cp[i][1]);
    }
    glEnd();
}

void BezierCurve()
{
    float t, x, y;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (t = 0.0; t <= 1.0; t += 0.01) {
        x = pow(1 - t, 3) * cp[0][0] +
            3 * t * pow(1 - t, 2) * cp[1][0] +
            3 * pow(t, 2) * (1 - t) * cp[2][0] +
            pow(t, 3) * cp[3][0];
        
        y = pow(1 - t, 3) * cp[0][1] +
            3 * t * pow(1 - t, 2) * cp[1][1] +
            3 * pow(t, 2) * (1 - t) * cp[2][1] +
            pow(t, 3) * cp[3][1];
        
        glVertex2f(x, y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ControlPoints();
    BezierCurve();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(150, 200);
    glutCreateWindow("Bezier Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
