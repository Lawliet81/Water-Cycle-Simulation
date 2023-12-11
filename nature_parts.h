// ------------------------------------------- Nature Parts -------------------------------------------------
#include "animations.h"
using namespace std;

// texture buffers
GLuint myTexture1;
GLuint myTexture2;
GLuint myTexture3;
GLuint myTexture4;
GLuint myTexture5;
GLuint myTexture6;
GLuint myTexture7;
GLuint myTexture8;
GLuint myTexture9;
GLuint myTexture10;
GLuint treeTexture;
GLuint landSurfaceTexture;
GLuint landSideTexture;
 
GLuint LoadTexture(const char *filename, int width, int height)
{

    // The following code will read in our RAW file
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        cout << "Unable to open the image file" << endl
             << "Program will exit :(" << endl;
        exit(0);
    }

    unsigned char *data = (unsigned char *)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    // reorder the image colors to RGB not BGR
    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B = data[index], R = data[index + 2];
        data[index] = R, data[index + 2] = B;
    }

    GLuint texture;
    glGenTextures(1, &texture);            // generate the texture with the loaded data
    glBindTexture(GL_TEXTURE_2D, texture); // bind the texture to it's array

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // set texture environment parameters

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // for sphere
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    free(data); // free the texture array

    if (glGetError() != GL_NO_ERROR)
        printf("GLError in genTexture()\n");

    if (texture == -1)
        cout << "Error in loading the texture" << endl;

    return texture; // return whether it was successfull
}

void init()
{

    // set backgroud color to sky blue color
    glClearColor(0.6f, 0.8f, 0.9f, 1.0f);

    // to make transparent in snowing and sun
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, ((double)win_width / win_height), 0.01f, 50);

    //------- Texture ---------
    myTexture1 = LoadTexture("Images/grass.bmp", 900, 900);          // grass
    myTexture2 = LoadTexture("Images/darkGround.bmp", 1200, 720);    // dark ground
    myTexture3 = LoadTexture("Images/ground.bmp", 1140, 1140);       // down of ground
    myTexture4 = LoadTexture("Images/lake.bmp", 588, 360);           // lake
    myTexture5 = LoadTexture("Images/waterflow.bmp", 800, 533);      // waterflow
    myTexture6 = LoadTexture("Images/water.bmp", 612, 408);          // water
    myTexture7 = LoadTexture("Images/sun5.bmp", 500, 500);           // Sun
    myTexture8 = LoadTexture("Images/snowSide.bmp", 1200, 720);     // snow side
    myTexture9 = LoadTexture("Images/mountain.bmp", 736, 736);       // mountain
    myTexture10 = LoadTexture("Images/snowSurface.bmp", 1024, 1024); // snow surface

    // cloud light
    GLfloat light_ambient[] = {0.7, 0.7, 0.7, 1};
    GLfloat light_diffuse[] = {0.9, 1, 1, 1};
    GLfloat light_cloudposition[] = {-0.8, 3.2, 1.0, 1};
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_cloudposition);

    // Rock light
    GLfloat white[] = {1, 1, 1, 1};
    GLfloat gray[] = {0.5, 0.5, 0.5, 1};
    GLfloat rockLightPosition[] = {-1.0, -4.2, 1.0, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, rockLightPosition);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, gray);
}
// draw cubic shape and put texture for grass or snow
void ground()
{

    glColor3f(1, 1, 1);

    // height = 0.5, width = 1.5, length = 2
    float A[] = {-1, 0.25, -0.5};
    float B[] = {1, 0.25, -0.5};
    float C[] = {-1, 0.25, 0.5};
    float D[] = {1, 0.25, 0.5};

    float E[] = {-1, -0.25, -0.5};
    float F[] = {1, -0.25, -0.5};
    float G[] = {-1, -0.25, 0.5};
    float H[] = {1, -0.25, 0.5};

    // will change the texture of land between grass and snow
    if (isSnow)
        landSurfaceTexture = myTexture10, landSideTexture = myTexture8;
    else
        landSurfaceTexture = myTexture1, landSideTexture = myTexture2;

    glEnable(GL_TEXTURE_2D);
    quadTexture(C, A, E, G, landSideTexture);
    quadTexture(A, B, F, E, landSideTexture);
    quadTexture(D, B, F, H, landSideTexture);
    quadTexture(C, D, H, G, landSideTexture);
    quadTexture(A, B, D, C, landSurfaceTexture); // up
    quadTexture(E, F, H, G, myTexture3);         // down
    glDisable(GL_TEXTURE_2D);
}

// draw ellips and put texture
GLvoid lake(const GLfloat radius, const GLuint num_vertex)
{

    glColor3f(0.20000, 0.80000, 1.00000);
    GLfloat vertex[4];
    GLfloat texcoord[2];

    const GLfloat delta_angle = 2.0 * M_PI / num_vertex;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture4);
    glBegin(GL_TRIANGLE_FAN);

    // draw the vertex at the center of the circle
    texcoord[0] = 0.5;
    texcoord[1] = 0.5;
    glTexCoord2fv(texcoord);

    vertex[0] = vertex[1] = vertex[2] = 0.0;
    vertex[3] = 1.0;
    glVertex4fv(vertex);

    for (int i = 0; i < num_vertex; i++)
    {

        texcoord[0] = (cos(delta_angle * i) + 1.0) * 0.5;
        texcoord[1] = (sin(delta_angle * i) + 1.0) * 0.5;
        glTexCoord2fv(texcoord);

        vertex[0] = cos(delta_angle * i) * radius;
        vertex[1] = sin(delta_angle * i) * radius;
        vertex[2] = 0.0;
        vertex[3] = 1.0;
        glVertex4fv(vertex);
    }

    texcoord[0] = (1.0 + 1.0) * 0.5;
    texcoord[1] = (0.0 + 1.0) * 0.5;
    glTexCoord2fv(texcoord);

    vertex[0] = 1.0 * radius;
    vertex[1] = 0.0 * radius;
    vertex[2] = 0.0;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// draw texture recatangles on surface and side of ground (cubic)
void waterfall()
{

    float A[3] = {-0.6, 0.251, -0.3};
    float B[3] = {-0.4, 0.251, -0.3};
    float C[3] = {-0.6, 0.251, 0.501};
    float D[3] = {-0.4, 0.251, 0.501};
    float E[3] = {-0.6, -0.5, 0.501};
    float F[3] = {-0.4, -0.5, 0.501};

    glColor3f(1, 1, 1);

    glEnable(GL_TEXTURE_2D);
    quadTexture(A, B, D, C, myTexture5);
    quadTexture(C, D, F, E, myTexture5);
    glDisable(GL_TEXTURE_2D);
}

// usign textured built-in sphere function
void sun(void)
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture7);
    glColor3f(1, 1, 0); // yellow
    GLUquadric *quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, GL_TRUE);    // Create Texture Coords
    gluQuadricNormals(quadratic, GLU_SMOOTH); // Create Smooth Normals
    gluSphere(quadratic, 0.15f, 20, 20);
    glDisable(GL_TEXTURE_2D);

    // light by making transparent sphere
    glEnable(GL_BLEND);
    glColor4f(1, 1, 0, 0.3f);
    glutSolidSphere(0.165, 20, 20);
    glDisable(GL_BLEND);
}

// by making white small pyramid
void mountainSnow(void)
{

    float a[3] = {0.51, 1.01, -0.51};
    float b[3] = {0.01, 0.01, -1.01};
    float c[3] = {1.01, 0.01, 0.01};
    float d[3] = {0.01, 0.01, 0.01};
    float e[3] = {1.01, 0.01, -1.01};

    glPushMatrix();
    glTranslatef(0.39, 0.8, -0.39);
    glScalef(0.21, 0.21, 0.21);
    glBegin(GL_TRIANGLES);
    glVertex3fv(a);
    glVertex3fv(e);
    glVertex3fv(b);

    glVertex3fv(a);
    glVertex3fv(e);
    glVertex3fv(c);

    glVertex3fv(b);
    glVertex3fv(d);
    glVertex3fv(a);

    glVertex3fv(a);
    glVertex3fv(d);
    glVertex3fv(c);
    glEnd();
    glPopMatrix();
}

void drawPyramid()
{

    float a[3] = {0.5, 1.0, -0.5};
    float b[3] = {0.0, 0.0, -1.0};
    float c[3] = {1.0, 0.0, 0.0};
    float d[3] = {0.0, 0.0, 0.0};
    float e[3] = {1.0, 0.0, -1.0};

    glColor3f(0.7, 0.5, 0.2); // brown

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture9);

    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(b);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(d);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(c);
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(e);
    glEnd();

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 0.5);
    glVertex3fv(a);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(e);
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(b);

    glTexCoord2f(0.5, 0.5);
    glVertex3fv(a);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(e);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(c);

    glTexCoord2f(0.0, 1.0);
    glVertex3fv(b);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(d);
    glTexCoord2f(0.5, 0.5);
    glVertex3fv(a);

    glTexCoord2f(0.5, 0.5);
    glVertex3fv(a);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(d);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(c);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    if (isSnow)
    {
        glEnable(GL_BLEND);
        glColor4f(1, 1, 1, snowTransparent);
        mountainSnow();
        glDisable(GL_BLEND);
    }
}

// group of texture pyramids
void mountain()
{

    glPushMatrix();
    glScalef(1.2, 1.2, 1.2);
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3, 0, 0);
    glRotatef(45, 0, 1, 0);
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, 0, 0);
    glRotatef(45, 0, 1, 0);
    drawPyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, 0, 0);
    glRotatef(-45, 0, 1, 0);
    drawPyramid();
    glPopMatrix();
}

// It`s a group of spheres of different sizes and postions
void oneCloud(void)
{

    // left
    glPushMatrix();
    glTranslated(-0.5, -0.1, 0);
    glutSolidSphere(0.35, 20, 20);
    glPopMatrix();

    // above right
    glPushMatrix();
    glTranslated(0.4, 0.2, 0);
    glutSolidSphere(0.25, 20, 20);
    glPopMatrix();

    // middle
    glutSolidSphere(0.5, 20, 20);

    // right
    glPushMatrix();
    glTranslated(0.5, -0.1, 0);
    glutSolidSphere(0.35, 20, 20);
    glPopMatrix();
}

void clouds(void)
{

    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);

    glColor3f(1, 1, 1); // white
    scaleAndTranslate(0.25 + goLeft, 0.9, -0.2, 0.1, oneCloud);
    scaleAndTranslate(-0.6 + goRight, 1.0, -0.3, 0.2, oneCloud);
    scaleAndTranslate(0.45 + goLeft, 0.95, -0.25, 0.15, oneCloud);
    scaleAndTranslate(-0.4 + goRight, 1.1, -0.4, 0.15, oneCloud);
    scaleAndTranslate(-0.06 + goRight, 1, -0.5, 0.2, oneCloud);
    scaleAndTranslate(0.25 + goLeft, 1, -0.3, 0.12, oneCloud);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHTING);
}

// drawi cylinder and 3 cones
void tree()
{

    // trunk
    GLUquadric *trunk = gluNewQuadric();
    glColor3f(0.5, 0.3, 0.1);
    glPushMatrix();
    glTranslatef(0.1, 0.49, 0.13);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(trunk, 0.04, 0.04, 0.4, 20, 20);
    glPopMatrix();

    // upper cone
    glColor4f(0.2, 0.4, 0.1, 1);
    glPushMatrix();
    glTranslatef(0.1, 1.25, 0.14);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.15, 0.3, 10, 10);
    glPopMatrix();

    // middle cone
    glColor4f(0.2, 0.3, 0.1, 1);
    glPushMatrix();
    glTranslatef(0.1, 1.07, 0.14);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.18, 0.3, 10, 10);
    glPopMatrix();

    // lower cone
    glColor4f(0.2, 0.4, 0.1, 1);
    glPushMatrix();
    glTranslatef(0.1, 0.9, 0.14);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.19, 0.3, 10, 10);
    glPopMatrix();

    // make snow by white small cone in above
    if (isSnow)
    {
        glEnable(GL_BLEND);
        glColor4f(1, 1, 1, snowTransparent);
        glPushMatrix();
        glTranslatef(0.1, 1.45, 0.15);
        glRotatef(-90, 1.0, 0.0, 0.0);
        glutSolidCone(0.07, 0.14, 10, 10);
        glPopMatrix();
        glDisable(GL_BLEND);
    }
}

// using built-in function to Dodecahedron shape and apply light on it
void rocks(void)
{

    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // behink lake
    scaleAndTranslate(0.6, 0.25, -0.3, 0.02, glutSolidDodecahedron);
    scaleAndTranslate(0.7, 0.25, -0.3, 0.035, glutSolidDodecahedron);

    // front of lake
    scaleAndTranslate(0.2, 0.25, 0.2, 0.025, glutSolidDodecahedron);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

// part of circle to draw steam
void arc()
{

    glLineWidth(4);
    double theta;
    glBegin(GL_LINE_STRIP);
    for (double i = 0; i <= 15; i++)
    {
        theta = i * 2.0 * M_PI / 360;
        glVertex2d(0.6f * cos(theta) + 0.9f, 0.9f * sin(theta) + 0.8f);
    }
    glEnd();
    glLineWidth(1);
}

void steam()
{

    glColor4f(0.1, 0.1, 0.1, 0.2); // transparent white
    glEnable(GL_BLEND);
    scaleAndTranslate(-0.9, smove, -0.1, 1, arc);
    scaleAndTranslate(-1, smove, -0.23, 1, arc);
    scaleAndTranslate(-0.8, smove, 0, 1, arc);
    scaleAndTranslate(-1.1, smove, -0.1, 1, arc);
    scaleAndTranslate(-1, smove, 0, 1, arc);
    glDisable(GL_BLEND);
}

void drop(void)
{

    // draw cone
    glPushMatrix();
    glRotatef(-5, 0, 0, 1);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.01, 0.05, 20, 20);
    glPopMatrix();

    // draw sphere
    glutSolidSphere(0.01, 20, 20);
}

// draw one line then rotate it
void iceCrystal(void)
{

    glColor3f(0.8, 0.9, 1.0); // light blue
    for (GLfloat theta = 0; theta < 360; theta += 60)
    {
        glPushMatrix();
        glRotatef(theta, 0, 0, 1);
        glBegin(GL_LINES);
        // vertical
        glVertex3f(0.0, 0.0, 0);
        glVertex3f(0, 0.5, 0);
        // first pair
        glVertex3f(0.1, 0.4, 0);
        glVertex3f(0.0, 0.3, 0);
        glVertex3f(-0.1, 0.4, 0);
        glVertex3f(0.0, 0.3, 0);
        // second pair
        glVertex3f(0.0, 0.18, 0);
        glVertex3f(0.12, 0.3, 0);
        glVertex3f(0.0, 0.18, 0);
        glVertex3f(-0.12, 0.3, 0);
        glEnd();
        glPopMatrix();
    }
}

// type of precipitation: rain, sleet and snow

void rain(void)
{

    if (t > keyFrameTimes[2] && t < keyFrameTimes[3])
    {
        glColor3f(0.3, 0.65, 1); // light blue
        for (int i = 0; i < NUMBER_OF_DROPS; i++)
            translate(dropsCoord[i][0], dropsCoord[i][1], dropsCoord[i][2], drop);
    }
}

void sleet(void)
{
    if (t > keyFrameTimes[3] && t < keyFrameTimes[4])
    {
        glColor4f(1, 1, 1, 1);
        for (int i = 0; i < NUMBER_OF_DROPS; i++)
        {
            glPushMatrix();
            glTranslatef(dropsCoord[i][0], dropsCoord[i][1], dropsCoord[i][2]);
            glutSolidSphere(0.01, 20, 20);
            glPopMatrix();
        }
    }
}

void snow(void)
{

    if (t > keyFrameTimes[4] && t < keyFrameTimes[5])
    {
        for (int i = 0; i < NUMBER_OF_DROPS; i++)
        {
            glPushMatrix();
            scaleAndTranslate(dropsCoord[i][0], dropsCoord[i][1], dropsCoord[i][2], 0.05, iceCrystal);
            glPopMatrix();
        }
    }
}

