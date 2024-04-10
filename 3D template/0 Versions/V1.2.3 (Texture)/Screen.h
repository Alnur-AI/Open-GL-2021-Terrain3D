#ifndef SCREEN_H
#define SCREEN_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

class Screen
{
public:
    GLFWwindow *window;

    int width = 800;
    int height = 600;

    float minViewDist = 2;
    float maxViewDist = 500;
};

#endif //SCREEN_H
