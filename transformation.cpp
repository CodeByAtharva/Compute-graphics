#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int wl = 1200;
int wh = 700;
float tx = 0, ty = 0; // Translation variables
float sx = 1, sy = 1; // Scaling variables
float angle = 0;      // Rotation angle
float shearX = 0, shearY = 0; // Shearing variables

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3i(0, 0, 0);
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // Apply transformations
    glTranslatef(tx, ty, 0); // Translation
    glScalef(sx, sy, 1);     // Scaling
    glRotatef(angle, 0, 0, 1); // Rotation
    glBegin(GL_LINES);

    // Draw a rectangle
    glVertex2i(250, 200); // Bottom-left
    glVertex2i(450, 200); // Bottom-right

    glVertex2i(450, 200); // Bottom-right
    glVertex2i(450, 350); // Top-right

    glVertex2i(450, 350); // Top-right
    glVertex2i(250, 350); // Top-left

    glVertex2i(250, 350); // Top-left
    glVertex2i(250, 200); // Bottom-left

    glEnd();

    glPopMatrix();
    glFlush();

}



void menu(int option) {
    switch (option) {
        case 1: // Translation
            tx += 50; // Example: Translate by 50 units in x-direction
            ty += 50; // Example: Translate by 50 units in y-direction
            break;
        case 2: // Scaling
            sx *= 1.2; // Scale up by 20%
            sy *= 1.2;
            break;
        case 3: // Rotation
            angle += 15; // Rotate by 15 degrees
            break;
        case 4: // Rotation about arbitrary point
            glTranslatef(300, 300, 0); // Translate to arbitrary point
            angle += 15; // Rotate
            glTranslatef(-300, -300, 0); // Translate back
            break;
        case 5: // Scaling about fixed point
            glTranslatef(300, 300, 0); // Translate to fixed point
            sx *= 1.2; // Scale up
            sy *= 1.2;
            glTranslatef(-300, -300, 0); // Translate back
            break;
        case 6: // Reflection
            sx = -sx; // Reflect across x-axis
            sy = sy; // Reflect across y-axis
            break;
        /*case 7: // Shear
            shearX += 10.0; // Shear in x-direction
            shearY += 0.2; // Shear in y-direction
            break;*/
        default:
            break;
    }
    glutPostRedisplay(); // Redraw the scene
}




int main(int c,char** v){

    glutInit(&c,v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl,wh);
    glutInitWindowPosition(100,50);
    glutCreateWindow("Transformation");

    glutDisplayFunc(display);
    myInit();

    // Create menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Translation", 1);
    glutAddMenuEntry("Scaling", 2);
    glutAddMenuEntry("Rotation", 3);
    glutAddMenuEntry("Rotation about arbitrary point", 4);
    glutAddMenuEntry("Scaling about fixed point", 5);
    glutAddMenuEntry("Reflection", 6);
    glutAddMenuEntry("Shear", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}