// -----------------------------------Helper Function------------------------------------------------------
// Put texture on quad
GLint win_width = 900, win_height = 900;
// Camera movement
GLfloat cameraPosition[] = {-1.5f, 1.5f, 2.0f};

void quadTexture(float v1[], float v2[], float v3[], float v4[], GLuint texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(1, 1);
    glVertex3fv(v1);
    glTexCoord2f(0, 1);
    glVertex3fv(v2);
    glTexCoord2f(0, 0);
    glVertex3fv(v3);
    glTexCoord2f(1, 0);
    glVertex3fv(v4);
    glEnd();
}

// apply uniform scaling then translate the passed function
void scaleAndTranslate(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat s, void (*shapeFunction)())
{
    glPushMatrix();
    glTranslatef(tx, ty, tz);
    glScalef(s, s, s);
    shapeFunction();
    glPopMatrix();
}

// translate the function
void translate(GLfloat x, GLfloat y, GLfloat z, void (*shapeFunction)())
{
    glPushMatrix();
    glTranslatef(x, y, z);
    shapeFunction();
    glPopMatrix();
}

void camera(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2], 0, 0, 0, 0, 1, 0);
}

void reshapeFunc(GLint new_width, GLint new_height)
{
    glViewport(0, 0, new_width, new_height);
    win_width = new_width;
    win_height = new_height;
}
