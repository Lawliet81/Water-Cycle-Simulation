static void play(void)
{

    // The scence has finished so,
    // reset the time and return the origin nature to start from begining
    if (t >= keyFrameTimes[5])
    {
        tex = 0; // for change text 
        t = 0;
        isSnow = false;                       // to change the nature to snowy
        glClearColor(0.6f, 0.8f, 0.9f, 1.0f); // light blue
        goLeft = goRight = 0;
        snowTransparent = 0;
    }

    // increase the timer
    t += 0.01;

    // the water cycle prosseses
    evaporate();
    condense();
    raining();
    sleeting();
    snowing();

    glutPostRedisplay();
}

// add text to screen
void addText(float x, float y, string str)
{

    glColor3f(1, 1, 1); // the font color is white
    glRasterPos2f(x, y);
    for (string::iterator c = (&str)->begin(); c != (&str)->end(); ++c)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}


void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera();

    glEnable(GL_DEPTH_TEST);

    // sun
    translate(0.6, 1.05, -0.4, sun);

    // ground
    ground();

    // mountain
    glPushMatrix();
    glTranslatef(-0.57, 0.2, 0.1);
    glRotatef(90, 0, 1, 0);
    glScalef(0.35, 0.6, 0.3);
    mountain();
    glPopMatrix();

    // trees
    scaleAndTranslate(0.0, 0, -0.4, 0.4, tree);
    scaleAndTranslate(-0.1, 0.1, 0.3, 0.3, tree);
    scaleAndTranslate(-0.25, 0, -0.1, 0.4, tree);
    scaleAndTranslate(0.8, 0, -0.4, 0.4, tree);

    // lake
    glPushMatrix();
    glTranslatef(0.5, 0.255, 0);
    glScalef(2.5, 1, 2);
    glRotatef(90, 1, 0, 0);
    lake(0.15, 100);
    glPopMatrix();

    waterfall();

    rocks();

    steam();

    clouds();

    // precipiting types
    rain();
    sleet();
    snow();

    glDisable(GL_DEPTH_TEST);

    // add text to screen that defines the process name
    addText(-0.2, -1.9, const_cast<char *>(a.c_str()));
    // addText(-1, 1.3, "Water Cycle");

   
    glFlush();
    glutSwapBuffers();
}
