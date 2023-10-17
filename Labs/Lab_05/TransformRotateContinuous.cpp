#include "TransformRotateContinuous.h"
#include "Application.h"



TransformRotateContinuous::TransformRotateContinuous()
    : TransformRotateContinuous(Rotation(), 0)
{ }

TransformRotateContinuous::TransformRotateContinuous(Rotation rotationRates, char pauseKey)
{
    this->rates = rotationRates;
    
    if(pauseKey != 0)
    {
        this->pauseKey = pauseKey;
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
    this->addTransform(this->rotateTransform);

    Application::getInstance()->registerKeyObserver(this);
}



glm::mat4 TransformRotateContinuous::getMatrix()
{
    this->setCurrentRotation();

    return TransformComposite::getMatrix();
}



void TransformRotateContinuous::keyHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(action == 1 && key == pauseKey)
    {
        if(!this->paused)
            this->setCurrentRotation(); // last rotation update before pause

        this->lastTick = (float)glfwGetTime();
        this->paused = !this->paused;
    }
}



void TransformRotateContinuous::setPauseKey(char pauseKey)
{
    this->pauseKey = pauseKey;
    this->pausable = true;
    
}

void TransformRotateContinuous::unsetPauseKey()
{
    this->pauseKey = 0;
    this->pausable = false;
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
