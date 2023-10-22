#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IMouseButtonObserver
{
public:
    virtual void mouseButtonPressedHandler(GLFWwindow* window, int button, int action, int mode) = 0;
};