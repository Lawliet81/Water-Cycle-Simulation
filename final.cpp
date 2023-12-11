
#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <cmath>
#include <mmsystem.h>
#include "helper.h"
#include "nature_parts.h"
#include "setup.h"
#include "CamMoveKeys.h"

int main(int argc, char **argv)
{

    // Initialize GLUT
    glutInit(&argc, argv);

    // number of buffers and depth for 3D shapes
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // Set the window's initial width & height
    glutInitWindowSize(win_width, win_height);

    // Position the window's initial top-left corner
    glutInitWindowPosition(0, 0);

    // title
    glutCreateWindow("Water Cycle Simulation");

    // some prepreation to draw as texture, lighting, etc.
    init();

    // display the draw and animation
    glutIdleFunc(play);
    glutDisplayFunc(display);

    // resize the window
    glutReshapeFunc(reshapeFunc);

    // keyboard input from user
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);

    // Enter the infinitely event-processing loop
    glutMainLoop();
}
