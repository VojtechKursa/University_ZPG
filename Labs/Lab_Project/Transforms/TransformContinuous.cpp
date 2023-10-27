#include "TransformContinuous.h"

#include "../Application.h"



TransformContinuous::TransformContinuous(ITransformContinuousable* transform, glm::vec3 rate, char pauseKey)
{
    this->transform = transform;
    this->rate = rate;
    
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

    this->paused = false;

    Application* app = Application::getInstance();
    app->registerKeyObserver(this);
    app->registerFrameObserver(this);
}

TransformContinuous::~TransformContinuous()
{
    Application* app = Application::getInstance();
    app->unregisterKeyObserver(this);
    app->unregisterFrameObserver(this);

    if(this->transform != nullptr)
    {
        delete this->transform;
        this->transform = nullptr;
    }
}



void TransformContinuous::setCurrentTransform(float timeSinceLastFrameSec)
{
    if(!this->paused)
    {
        this->transform->increaseTransformParameter(this->rate * timeSinceLastFrameSec);
    }
}



void TransformContinuous::setPauseKey(char pauseKey)
{
    this->pauseKey = pauseKey;
    this->pausable = true;
    
}

void TransformContinuous::unsetPauseKey()
{
    this->pauseKey = 0;
    this->pausable = false;
}



glm::mat4 TransformContinuous::getMatrix()
{
    return this->transform->getMatrix();
}



void TransformContinuous::keyHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(action == 1 && key == pauseKey)
    {
        this->paused = !this->paused;
    }
}

void TransformContinuous::frameHandler(double timeSinceLastFrameSec)
{
    this->setCurrentTransform(timeSinceLastFrameSec);
}
