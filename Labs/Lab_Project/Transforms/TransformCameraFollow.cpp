#include "TransformCameraFollow.h"

#include "../Application.h"
#include "../Events/CameraEventData.h"



TransformCameraFollow::TransformCameraFollow(Camera *camera)
    : TransformTranslate(camera->getPosition())
{
    this->camera = camera;

    this->camera->registerObserver(this);
    Application::getInstance()->registerObserver(this);
}

TransformCameraFollow::~TransformCameraFollow()
{
    this->camera->unregisterObserver(this);
    Application::getInstance()->unregisterObserver(this);
}



void TransformCameraFollow::notify(const Event *event)
{
    switch(event->eventType)
    {
        case EVENT_CAMERA:
            this->updatePos();
            break;
        case EVENT_KEY:
            this->keyHandler(static_cast<const KeyEventData*>(event->data));
            break;
    }
}



void TransformCameraFollow::keyHandler(const KeyEventData* eventData)
{
    if (eventData->key == GLFW_KEY_B && eventData->mods == GLFW_MOD_ALT && eventData->action == GLFW_PRESS)
    {
        this->following = !this->following;

        if (this->following)
            this->updatePos();
    }
}

void TransformCameraFollow::updatePos()
{
    if (this->following)
    {
        this->translationVector = this->camera->getPosition();
    }
}
