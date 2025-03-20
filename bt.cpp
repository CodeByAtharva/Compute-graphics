#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int wl = 1200;
int wh = 700;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3i(0, 0, 0);
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    //glPushMatrix(); // use to save the current transformation matrix onto a stack this function is deprecated from the opengl

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
            glTranslatef(-200,0,0);

            break;
        case 2: // Scaling
            glScalef(2,2,1);

            break;
        case 3: // Rotation
            glRotatef(45,0,0,1);

            break;
        case 4: // Rotation about arbitrary point
            glTranslatef(300, 300, 0); // Translate to arbitrary point (300, 300)
            glRotatef(45, 0, 0, 1);    // Rotate by 45 degrees
            glTranslatef(-300, -300, 0); // Translate back

            break;
        case 5: // Scaling about fixed point
            glTranslatef(300, 300, 0); // Translate to fixed point (300, 300)
            glScalef(2, 2, 1);         // Scale by a factor of 2
            glTranslatef(-300, -300, 0); // Translate back
            break;
        case 6: // Reflection
            glScalef(-1, 1, 1);
 
            break;
        case 7: // Shear

        {
            // Define the shear matrix
            float shx = 0.5f; // Shear factor in x-direction
            float shy = 0.2f; // Shear factor in y-direction
            float shearMatrix[16] = {
                1, shx, 0, 0, // First column
                shy, 1,  0, 0, // Second column
                0,  0,  1, 0, // Third column
                0,  0,  0, 1  // Fourth column
            };

            // Apply the shear matrix
            glMultMatrixf(shearMatrix);
            break;
        }

            break;
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