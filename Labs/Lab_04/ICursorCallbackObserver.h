#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ICursorCallbackObserver
{
public:
    virtual void cursor_callback(GLFWwindow* window, double x, double y) = 0;
};