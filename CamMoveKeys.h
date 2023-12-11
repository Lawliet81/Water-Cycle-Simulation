void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'z':
        // Move camera forward along the Z-axis
        cameraPosition[2] -= 0.1;
        break;
    case 'Z':
        // Move camera backward along the Z-axis
        cameraPosition[2] += 0.1;
        break;
    case 'x':
        // Move camera to the right along the X-axis
        cameraPosition[0] += 0.1;
        break;
    case 'X':
        // Move camera to the left along the X-axis
        cameraPosition[0] -= 0.1;
        break;
    case 'y':
        // Move camera down along the Y-axis
        cameraPosition[1] -= 0.1;
        break;
    case 'Y':
        // Move camera up along the Y-axis
        cameraPosition[1] += 0.1;
        break;
    case 27: // ASCII code for 'esc'
        // Exit the program
        exit(0);
        break;
    default:
        fprintf(stderr, "\nKeyboard commands:\nZ - Move forward along Z-axis\nz - Move backward along Z-axis\nX - Move left along X-axis\nx - Move right along X-axis\nY - Move up along Y-axis\ny - Move down along Y-axis\n<esc> - Quit\n");
    }

    // Print the camera position
    printf("camera position: (%0.1f, %0.1f, %0.1f)\n",
           cameraPosition[0], cameraPosition[1], cameraPosition[2]);
}


void specialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        // Move camera to the right along the X-axis
        cameraPosition[0] = (cameraPosition[0] >= 6) ? -3.5 : cameraPosition[0] + 0.1;
        break;
    case GLUT_KEY_LEFT:
        // Move camera to the left along the X-axis
        cameraPosition[0] = (cameraPosition[0] <= -6) ? 3.5 : cameraPosition[0] - 0.1;
        break;
    case GLUT_KEY_UP:
        // Move camera up along the Y-axis
        cameraPosition[1] = (cameraPosition[1] >= 6) ? -2.0 : cameraPosition[1] - 0.1;
        break;
    case GLUT_KEY_DOWN:
        // Move camera down along the Y-axis
        cameraPosition[1] = (cameraPosition[1] <= -6) ? 2.0 : cameraPosition[1] + 0.1;
        break;
    default:
        break;
    }

    // Print the camera position
    printf("camera position: (%0.1f, %0.1f, %0.1f)\n",
           cameraPosition[0], cameraPosition[1], cameraPosition[2]);
}
