#include "TransformContinuous.h"

#include "../Application.h"

#include "../Events/KeyEventData.h"
#include "../Events/FrameEventData.h"



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

    Application::getInstance()->registerObserver(this);
}

TransformContinuous::~TransformContinuous()
{
    Application::getInstance()->unregisterObserver(this);

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



void TransformContinuous::notify(const Event *event)
{
    switch(event->eventType)
    {
        case EVENT_KEY:
        {
            const KeyEventData* data = static_cast<const KeyEventData*>(event->data);
            this->keyHandler(data->key, data->scanCode, data->action, data->mods);
            break;
        }
        case EVENT_FRAME:
        {
            const FrameEventData* data = static_cast<const FrameEventData*>(event->data);
            this->frameHandler(data->timeSinceLastFrameSec);
            break;
        }
    }
}

void TransformContinuous::keyHandler(int key, int scancode, int action, int mods)
{
    if(action == 1 && key == pauseKey)
    {
        this->paused = !this->paused;
    }
}

void TransformContinuous::frameHandler(double timeSinceLastFrameSec)
{
    this->setCurrentTransform(static_cast<float>(timeSinceLastFrameSec));
}
