#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IKeyCallbackObserver
{
public:
    virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};