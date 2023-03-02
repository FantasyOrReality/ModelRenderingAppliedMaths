

// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;

float windowWidth = 500, windowHeight = 500;

// ----------------------------------------------------------
// Function to draw the cube model using primitives
// ----------------------------------------------------------
void drawCube()
{
    // DRAW MODEL

   //Multi-colored side - FRONT
    glBegin(GL_POLYGON);

    glColor3f(1.0, 0.0, 0.0);     glVertex3f(0.5, -0.5, -0.5);      // P1 is red
    glColor3f(0.0, 1.0, 0.0);     glVertex3f(0.5, 0.5, -0.5);      // P2 is green
    glColor3f(0.0, 0.0, 1.0);     glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
    glColor3f(1.0, 0.0, 1.0);     glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple

    glEnd();

    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display() {

    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ------------------------------------------------------
    // PROJECTION MATRIX
    //-------------------------------------------------------
    // Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Clipping planes, used for both Ortho and Perspective
    float clipNear = 0.1f;
    float clipFar = 100.0f;

    // Orthographic view - no perspective
    // straight field of view/tunnel vision
    float orthoLeft = -1.0f;
    float orthoRight = 1.0f;
    float orthoTop = 1.0f;
    float orthoBottom = -1.0f;

    //glOrtho(orthoLeft, orthoRight, orthoBottom, orthoTop, 
    //  clipNear, clipFar);

    // Perspective view , different view based on camera position
    // views wider field of view
    float fov = 90.0f;
    float aspectRatio = windowWidth / windowHeight;
    gluPerspective(fov, aspectRatio, clipNear, clipFar);


    // ------------------------------------------------------
    // VIEW AND MODEL MATRICES COMBINED
    //-------------------------------------------------------
    // Setup the matrix to be edited
    glMatrixMode(GL_MODELVIEW);


    // Reset the matrix
    glLoadIdentity();

    // ------------------------------------------------------
    // VIEW TRANSFORMS  
    // ------------------------------------------------------
    // Camera position
    float cameraX = 0.0f;
    float cameraY = 0.0f;
    float cameraZ = -1.0f;

    // Looking at position
    float lookX = 0.0f;
    float lookY = 0.0f;
    float lookZ = 0.0f;

    // Up matrix positon
    float upX = 0.0f;
    float upY = 1.0f;
    float upZ = 0.0f;

    gluLookAt(cameraX, cameraY, cameraZ,
        lookX, lookY, lookZ,
        upX, upY, upZ);


    // ------------------------------------------------------
    // MODEL TRANSFORMS | TRS | Translate, Rotate, Scale
    // ------------------------------------------------------

    // Translate to set location
    glTranslatef(0.0f, 0.0f, 0.0f);

    // Rotate tp the correct angles
    glRotatef(rotate_y, 0.0f, 1.0f, 0.0f); //yaw, y axis
    glRotatef(rotate_x, 1.0f, 0.0f, 0.0f); //pitch, x axis
    glRotatef(0, 0.0f, 1.0f, 1.0f); //roll, z axis

    // Scale to desired dimensions
    glScalef(1.0f, 1.0f, 1.0f);

    // MODEL - draw the cube
    drawCube();


    // END of display - flush and swap buffers
    glFlush();
    glutSwapBuffers();

}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;

    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;

    else if (key == GLUT_KEY_UP)
        rotate_x += 5;

    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;

    //  Request display update
    glutPostRedisplay();

}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]) {

    //  Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    //  Request double buffered true color window with Z-buffer
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutCreateWindow("Awesome Cube");

    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    //  Pass control to GLUT for events
    glutMainLoop();

    //  Return to OS
    return 0;

}