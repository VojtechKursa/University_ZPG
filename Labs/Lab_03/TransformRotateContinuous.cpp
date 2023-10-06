#include "TransformRotateContinuous.h"
#include "Application.h"



TransformRotateContinuous::TransformRotateContinuous()
    : TransformRotateContinuous(Rotation(0,0,0), nullptr)
{ }

TransformRotateContinuous::TransformRotateContinuous(Rotation rotationRates, char *pauseKey)
{
    this->rates = rotationRates;
    
    if(pauseKey != nullptr)
    {
        this->pauseKey = *pauseKey;
        this->pausable = true;
    }
    else
    {
        this->pauseKey = 0;
        this->pausable = false;
    }

    this->lastTick = (float)glfwGetTime();
    this->paused = false;

    this->rotateTransform = new TransformRotate();

    Application::getInstance().registerKeyListener(this);
}



void TransformRotateContinuous::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(action == 0 && key == pauseKey)
    {
        if(!this->paused)
            this->setCurrentRotation(); // last rotation update before pause

        this->lastTick = (float)glfwGetTime();
        this->paused = !this->paused;
    }
}

glm::mat4 TransformRotateContinuous::getMatrix()
{
    this->setCurrentRotation();

    return this->rotateTransform->getMatrix();
}

void TransformRotateContinuous::setPauseKey(char *pauseKey)
{
    if(pauseKey != nullptr)
    {
        this->pauseKey = *pauseKey;
        this->pausable = true;
    }
    else
    {
        this->pauseKey = 0;
        this->pausable = false;
    }
}

void TransformRotateContinuous::setCurrentRotation()
{
    if(!this->paused)
    {
        float currTime = (float)glfwGetTime();
        float timeDiff = currTime - this->lastTick;

        this->rotateTransform->setRotation(this->rotateTransform->getRotation() + timeDiff * this->rates);
        
        this->lastTick = currTime;
    }
}
