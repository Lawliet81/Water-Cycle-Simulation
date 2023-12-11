// -------------------------------------------------Animation-----------------------------------------------
using namespace std;
// for animation
string a;
float tex = 0;
bool isSnow = false;                               // to change the land to snowy
GLfloat smove = -0.9;                              // evaporate steam
GLfloat goLeft = 0, goRight = 0;                   // for cloud movements
GLfloat snowTransparent = 0.2;                     // for snow appearing
GLfloat keyFrameTimes[] = {0, 17, 23, 35, 45, 55}; // t starting values of keyframes
GLfloat t = 0;
const int NUMBER_OF_DROPS = 100;
GLfloat dropsCoord[NUMBER_OF_DROPS][3] = {
    {-0.14, 0.84, -0.33}, {-0.23, 0.48, -0.25}, {0.06, 0.23, -0.27}, {0.23, 0.50, -0.25}, {0.06, 0.23, -0.27}, {-0.23, 0.68, -0.25}, {0.24, 0.42, -0.35}, {0.06, 0.75, -0.32}, {0.31, 0.78, -0.31}, {0.30, 0.65, -0.25}, {0.35, 0.60, -0.32}, {0.31, 0.78, -0.21}, {0.08, 0.49, -0.25}, {0.27, 0.52, -0.37}, {-0.09, 0.43, -0.31}, {0.31, 0.25, -0.27}, {-0.10, 0.77, -0.25}, {-0.16, 0.86, -0.19}, {-0.21, 0.25, -0.34}, {-0.27, 0.41, -0.22}, {0.09, 0.56, -0.23}, {0.03, 0.72, -0.38}, {-0.22, 0.49, -0.28}, {-0.05, 0.44, -0.35}, {0.18, 0.78, -0.36}, {-0.19, 0.34, -0.30}, {-0.30, 0.21, -0.27}, {-0.14, 0.64, -0.20}, {-0.04, 0.90, -0.22}, {0.19, 0.60, -0.38}, {0.08, 0.61, -0.30}, {0.31, 0.45, -0.29}, {0.23, 0.29, -0.29}, {0.27, 0.71, -0.32}, {-0.10, 0.63, -0.34}, {-0.11, 0.22, -0.23}, {0.26, 0.31, -0.35}, {0.24, 0.85, -0.32}, {-0.01, 0.26, -0.24}, {-0.29, 0.78, -0.35}, {0.24, 0.42, -0.35}, {0.06, 0.75, -0.32}, {0.31, 0.78, -0.31}, {-0.11, 0.33, -0.39}, {0.06, 0.23, -0.27}, {0.35, 0.50, -0.27}, {-0.35, 0.70, -0.31}, {-0.30, 0.40, -0.39}, {-0.39, 0.64, -0.27}, {-0.35, 0.56, -0.27}};

// first keyfram t0
void evaporate(void)
{
    // it`s still in its keyframe time, so make the animation
    if (t > keyFrameTimes[0] && t < keyFrameTimes[1])
    {
        smove += 0.0004;
    }
    else // it reached the cloud so disappear inside the ground
    {
        smove = -0.9;
    }

    if (tex == 0)
    {
        // for change text
        a = ("Evaporation");
        tex++;
    }
}

// second keyfram t1
void condense(void)
{

    if (t > keyFrameTimes[1] && t < keyFrameTimes[2])
    {

        // change background color
        glClearColor(0.45882, 0.61961, 0.74118, 1);

        // move the clouds
        goLeft -= 0.0005;
        goRight += 0.0005;

        // for change text
        if (tex == 1)
        {
            a = ("Condensation");
            tex++;
        }
    }
}

// each type has it own speed
void precipiting(double speed)
{

    // by update drop y position and if hit the ground start from begining
    // 0.25 the ground, 0.85 height of clouds
    for (int i = 0; i < NUMBER_OF_DROPS; i++)
        dropsCoord[i][1] = dropsCoord[i][1] <= 0.25 ? 0.85 : dropsCoord[i][1] -= speed;
}

// third keyfram t2
void raining(void)
{

    if (t > keyFrameTimes[2] && t < keyFrameTimes[3])
    {
        glClearColor(0.39216, 0.57255, 0.70588, 1); // change color background
        precipiting(0.005f);                        // start raining

        if (tex == 2)
        {

            // for change text
            a = ("Precipitation-Rain");
            tex++;
        }
    }
}

// fourth keyfram t3
void sleeting(void)
{

    if (t > keyFrameTimes[3] && t < keyFrameTimes[4])
    {
        glClearColor(0.32549, 0.52157, 0.67451, 1); // change color background
        precipiting(0.002f);                        // start sleet

        if (tex == 3)
        {

            // add text
            a = ("Or Precipitation-Sleet");
            tex++;
        }
    }
}

// sixth and final keyfram t5
void snowing(void)
{

    if (t > keyFrameTimes[4] && t < keyFrameTimes[5])
    {
        isSnow = true;                              // to change the nature to snowy
        glClearColor(0.29412, 0.47059, 0.60784, 1); // change color background
        precipiting(0.001f);                        // start snowing
        snowTransparent += 0.001f;

        if (tex == 4)
        {

            // add text
            a = ("Or Precipitation-Snowflakes");
            tex++;
        }
    }
}