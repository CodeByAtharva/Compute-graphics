#include <GL/glut.h>
#include <cmath> // For sin, cos

float flagY = -0.8f;  
bool hoisting = true;
float wavePhase = 0.0f; // For moving waves

void init() {
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);  
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1);  
}

void drawAshokaChakra(float centerX, float centerY, float radius) {
    int spokes = 24;
    float angle;

    // Outer circle
    glColor3f(0.0f, 0.0f, 0.5f);  
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        angle = 2.0f * M_PI * i / 100;
        glVertex2f(centerX + cos(angle) * radius, centerY + sin(angle) * radius);
    }
    glEnd();

    // Spokes
    glBegin(GL_LINES);
    for (int i = 0; i < spokes; i++) {
        angle = 2.0f * M_PI * i / spokes;
        glVertex2f(centerX, centerY);
        glVertex2f(centerX + cos(angle) * radius, centerY + sin(angle) * radius);
    }
    glEnd();
}

void drawWaveBand(float topY, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUAD_STRIP);
    for (float x = 0.02f; x <= 0.4f; x += 0.01f) {
        float yOffset = 0.01f * sin(10 * x + wavePhase); // wavy offset
        glVertex2f(x, topY + yOffset);
        glVertex2f(x, topY + height + yOffset);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Flag Pole
    glColor3f(0.4f, 0.2f, 0.0f);  
    glBegin(GL_POLYGON);
        glVertex2f(-0.02f, -0.8f);
        glVertex2f( 0.02f, -0.8f);
        glVertex2f( 0.02f, 0.8f);
        glVertex2f(-0.02f, 0.8f);
    glEnd();

    // Draw Flag
    drawWaveBand(flagY, 0.06f, 0.0f, 0.5f, 0.0f); // Green band (bottom)
    drawWaveBand(flagY + 0.06f, 0.06f, 1.0f, 1.0f, 1.0f); // White band (middle)
    drawWaveBand(flagY + 0.12f, 0.06f, 1.0f, 0.6f, 0.0f); // Saffron band (top)

    // Draw Ashoka Chakra
    glPushMatrix();
        float centerOffset = 0.01f * sin(10 * 0.21f + wavePhase); // Chakra moves slightly with wave
        drawAshokaChakra(0.21f, flagY + 0.09f + centerOffset, 0.02f);
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    if (hoisting) {
        if (flagY < 0.6f) {
            flagY += 0.01f;
            glutPostRedisplay();
            glutTimerFunc(50, update, 0);
        } else {
            hoisting = false;
            glutTimerFunc(30, update, 0);
        }
    } else {
        wavePhase += 0.1f; // Keep waving
        glutPostRedisplay();
        glutTimerFunc(30, update, 0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Realistic Waving Flag 🇮🇳");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}