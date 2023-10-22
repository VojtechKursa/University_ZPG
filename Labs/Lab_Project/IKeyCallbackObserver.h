#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IKeyCallbackObserver
{
public:
    virtual void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};