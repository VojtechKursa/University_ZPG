#include "TransformCameraFollow.h"

#include "../Events/CameraEventData.h"



TransformCameraFollow::TransformCameraFollow(Camera *camera)
    : TransformTranslate(camera->getPosition())
{
    this->camera = camera;

    this->camera->registerObserver(this);
}

TransformCameraFollow::~TransformCameraFollow()
{
    this->camera->unregisterObserver(this);
}



void TransformCameraFollow::notify(const Event *event)
{
    switch(event->eventType)
    {
        case EVENT_CAMERA:
            this->translationVector = static_cast<const CameraEventData*>(event->data)->cameraPosition;
            break;
    }
}
