#include <GL/glut.h>
#include <cmath>
#include <vector>

// Increased grid resolution for more detail
const int gridSize = 150;
float waterHeight[gridSize][gridSize] = {0};
float waterColor[gridSize][gridSize][3]; // RGB color for each vertex

// Droplet properties
float dropletY = 2.0f;
bool hasDropped = false;
float timeSinceDrop = 0.0f;
const float dropSpeed = 0.05f;

// Multiple wave centers for complex patterns
const int MAX_WAVES = 5;
float waveCenters[MAX_WAVES][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
float waveStarts[MAX_WAVES] = {0};
int activeWaves = 1;

// Surface settings - significantly increased to cover screen
float surfaceSize = 30.0f; // Much larger surface area to fill entire window
float spacing = surfaceSize / gridSize;

// Lighting parameters - adjusted for deeper blue effect
GLfloat light_position[] = {2.0f, 5.0f, 3.0f, 1.0f};
GLfloat light_ambient[] = {0.3f, 0.3f, 0.5f, 1.0f};
GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

// Material properties - adjusted for deeper blue water
GLfloat mat_ambient[] = {0.1f, 0.3f, 0.7f, 0.8f};  // Deeper blue
GLfloat mat_diffuse[] = {0.2f, 0.5f, 0.9f, 0.8f};  // More saturated blue
GLfloat mat_specular[] = {0.7f, 0.8f, 1.0f, 0.8f}; // Stronger highlights
GLfloat mat_shininess[] = {80.0f}; // Higher shininess for water sheen

// Function to calculate water surface normals
void calculateNormals(float normals[gridSize][gridSize][3]) {
    for (int i = 1; i < gridSize-1; i++) {
        for (int j = 1; j < gridSize-1; j++) {
            // Calculate tangent vectors using central differences
            float tangentX[3] = {
                2.0f * spacing,
                waterHeight[i+1][j] - waterHeight[i-1][j],
                0.0f
            };
           
            float tangentZ[3] = {
                0.0f,
                waterHeight[i][j+1] - waterHeight[i][j-1],
                2.0f * spacing
            };
           
            // Cross product to get normal
            normals[i][j][0] = tangentZ[1] * tangentX[2] - tangentZ[2] * tangentX[1];
            normals[i][j][1] = tangentZ[2] * tangentX[0] - tangentZ[0] * tangentX[2];
            normals[i][j][2] = tangentZ[0] * tangentX[1] - tangentZ[1] * tangentX[0];
           
            // Normalize
            float length = sqrt(normals[i][j][0] * normals[i][j][0] +
                              normals[i][j][1] * normals[i][j][1] +
                              normals[i][j][2] * normals[i][j][2]);
           
            if (length > 0.0f) {
                normals[i][j][0] /= length;
                normals[i][j][1] /= length;
                normals[i][j][2] /= length;
            } else {
                normals[i][j][0] = 0.0f;
                normals[i][j][1] = 1.0f;
                normals[i][j][2] = 0.0f;
            }
        }
    }
   
    // Set border normals to match their neighbors
    for (int i = 0; i < gridSize; i++) {
        normals[i][0][0] = normals[i][1][0];
        normals[i][0][1] = normals[i][1][1];
        normals[i][0][2] = normals[i][1][2];
       
        normals[i][gridSize-1][0] = normals[i][gridSize-2][0];
        normals[i][gridSize-1][1] = normals[i][gridSize-2][1];
        normals[i][gridSize-1][2] = normals[i][gridSize-2][2];
    }
   
    for (int j = 0; j < gridSize; j++) {
        normals[0][j][0] = normals[1][j][0];
        normals[0][j][1] = normals[1][j][1];
        normals[0][j][2] = normals[1][j][2];
       
        normals[gridSize-1][j][0] = normals[gridSize-2][j][0];
        normals[gridSize-1][j][1] = normals[gridSize-2][j][1];
        normals[gridSize-1][j][2] = normals[gridSize-2][j][2];
    }
}

// Function to add a new wave
void addWave(float x, float z) {
    if (activeWaves < MAX_WAVES) {
        waveCenters[activeWaves][0] = x;
        waveCenters[activeWaves][1] = z;
        waveStarts[activeWaves] = timeSinceDrop;
        activeWaves++;
    }
}

// Reset simulation
void resetSimulation() {
    hasDropped = false;
    dropletY = 2.0f;
    timeSinceDrop = 0.0f;
    activeWaves = 1;
   
    // Reset water heights
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            waterHeight[i][j] = 0.0f;
        }
    }
}

// Draw a realistic water droplet with cone and semicircle
void drawWaterDroplet(float y) {
    glColor4f(0.2f, 0.4f, 0.8f, 0.8f); // Darker blue droplet to match the new water color
   
    // Define clip plane equation coefficients
    GLdouble clipPlane[4] = {0.0, -1.0, 0.0, 0.0};
   
    // Draw the semicircle (top part)
    glPushMatrix();
    glTranslatef(0.0f, y, 0.0f);
    // Cut the sphere in half to create a hemisphere
    glClipPlane(GL_CLIP_PLANE0, clipPlane);
    glEnable(GL_CLIP_PLANE0);
    glutSolidSphere(0.08f, 20, 20);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
   
    // Draw the cone (bottom part)
    glPushMatrix();
    glTranslatef(0.0f, y, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotate to point downward
    glutSolidCone(0.08f, 0.15f, 20, 20);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
   
    // Revised camera position - looking almost directly down on the water
    // with slight angle to provide some perspective
    gluLookAt(0.0f, 15.0f, 0.1f,  // Camera positioned high up, minimal Z offset
              0.0f, 0.0f, 0.0f,   // Look at center
              0.0f, 0.0f, -1.0f); // Changed up vector to achieve proper orientation
   
    // Calculate normals for lighting
    float normals[gridSize][gridSize][3];
    calculateNormals(normals);
   
    // Draw rippling water surface with improved lighting
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   
    // Draw water surface with detailed normals
    for (int i = 0; i < gridSize - 1; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < gridSize; j++) {
            float x1 = (i * spacing) - surfaceSize / 2;
            float z1 = (j * spacing) - surfaceSize / 2;
           
            float x2 = ((i+1) * spacing) - surfaceSize / 2;
            float z2 = (j * spacing) - surfaceSize / 2;
           
            // Set color based on wave height for subtle water depth effect
            // Deeper blue colors with white highlights for ripples
            float depthIntensity1 = 0.7f + 0.3f / (1.0f + fabs(waterHeight[i][j] * 8.0f));
            float depthIntensity2 = 0.7f + 0.3f / (1.0f + fabs(waterHeight[i+1][j] * 8.0f));
           
            // First vertex - deeper blue colors
            glNormal3fv(normals[i][j]);
            glColor3f(depthIntensity1 * 0.2f, depthIntensity1 * 0.5f, depthIntensity1 * 1.0f);
            glVertex3f(x1, waterHeight[i][j], z1);
           
            // Second vertex
            glNormal3fv(normals[i+1][j]);
            glColor3f(depthIntensity2 * 0.2f, depthIntensity2 * 0.5f, depthIntensity2 * 1.0f);
            glVertex3f(x2, waterHeight[i+1][j], z2);
        }
        glEnd();
    }
   
    // Draw droplet
    if (!hasDropped) {
        glDisable(GL_LIGHTING);
       
        // Draw the realistic water droplet with cone and semicircle
        drawWaterDroplet(dropletY);
       
        // Add a subtle trail behind the droplet
        glBegin(GL_LINES);
        for (int i = 0; i < 10; i++) {
            float trailY = dropletY + 0.02f * i;
            float alpha = 1.0f - i * 0.1f;
            if (trailY < 2.0f) {
                glColor4f(0.2f, 0.4f, 0.8f, alpha * 0.5f); // Darker blue trail
                glVertex3f(0.0f, trailY, 0.0f);
                glVertex3f(0.0f, trailY + 0.02f, 0.0f);
            }
        }
        glEnd();
       
        glEnable(GL_LIGHTING);
    }
   
    glutSwapBuffers();
}

void update(int value) {
    if (!hasDropped) {
        dropletY -= dropSpeed;
       
        // When droplet hits the water
        if (dropletY <= 0.05f) {
            hasDropped = true;
            // Center the first wave at the impact point
            waveCenters[0][0] = 0.0f;  // x center
            waveCenters[0][1] = 0.0f;  // z center
        }
    } else {
        timeSinceDrop += 0.04f;
       
        // Create gentler, more subtle waves to match the reference image
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                float x = (i * spacing) - surfaceSize / 2;
                float z = (j * spacing) - surfaceSize / 2;
               
                // Start with flat water
                waterHeight[i][j] = 0.0f;
               
                // Add effects from all active waves - more subtle than before
                for (int wave = 0; wave < activeWaves; wave++) {
                    float waveTimeFactor = timeSinceDrop - waveStarts[wave];
                   
                    if (waveTimeFactor > 0) {
                        float dx = x - waveCenters[wave][0];
                        float dz = z - waveCenters[wave][1];
                        float dist = sqrt(dx * dx + dz * dz);
                       
                        // Wave radius grows over time - gentler propagation
                        float waveRadius = waveTimeFactor * 1.2f;
                       
                        // Gentler, smoother waves with wider radius
                        float thickness = 0.5f;  // Thicker, smoother wave ring
                        float ringFactor = exp(-pow((dist - waveRadius) / thickness, 2.0f));
                                         
                        // Lower amplitude for more gentle ripples
                        float amplitude = 0.08f * exp(-waveTimeFactor * 0.3f);  // Wave decays over time
                                         
                        // Add this wave's contribution - gentler frequency
                        waterHeight[i][j] += amplitude * ringFactor * sin(dist * 5.0f - waveTimeFactor * 4.0f);
                                         
                        // Add smaller secondary interference waves - more subtle
                        waterHeight[i][j] += 0.02f * amplitude * sin(dist * 10.0f - waveTimeFactor * 5.0f) * ringFactor;
                    }
                }
               
                // Add gentle ambient water movement
                waterHeight[i][j] += 0.005f * sin(x * 1.5f + timeSinceDrop * 0.8f) * cos(z * 1.5f + timeSinceDrop * 0.6f);
            }
        }
       
        // Fewer secondary waves for a calmer surface
        if (timeSinceDrop > 1.0f && timeSinceDrop < 2.0f && (int)(timeSinceDrop * 20) % 15 == 0) {
            // Add a secondary ripple point near the center - smaller offset for less chaotic pattern
            float offsetX = ((rand() % 100) / 100.0f - 0.5f) * 0.3f;
            float offsetZ = ((rand() % 100) / 100.0f - 0.5f) * 0.3f;
            addWave(offsetX, offsetZ);
        }
       
        // Reset animation after waves have dissipated
        if (timeSinceDrop > 5.0f) {
            resetSimulation();
        }
    }
   
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.2f, 0.5f, 1.0f); // Darker blue background
   
    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   
    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
   
    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    // Initialize wave centers
    waveCenters[0][0] = 0.0f;
    waveCenters[0][1] = 0.0f;
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Wider field of view - closer to orthographic projection for better screen filling
    gluPerspective(80.0, (float)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    // Reset simulation with 'r' key
    if (key == 'r' || key == 'R') {
        resetSimulation();
    }
    // Exit with 'esc' key
    else if (key == 27) {
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Blue Water Surface Simulation");
   
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
   
    glutMainLoop();
    return 0;
}