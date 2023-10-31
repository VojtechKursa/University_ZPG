#include "OrbittingObject.h"

#include "Application.h"

#include "Events/FrameEventData.h"



OrbittingObject::OrbittingObject(Model *model, ShaderProgram *shaderProgram, Transform* transform, glm::vec3 pivotAxis, float rotationRate, glm::vec3 pivotPosition, glm::vec3 startingRelativePosition, Material material)
    : DrawableObject(model, shaderProgram, material)
{
    this->rotationRate = rotationRate;
    this->startingRelativePosition = glm::vec4(startingRelativePosition, 1.0);

    this->pivotPosition = pivotPosition;
    this->pivotObject = nullptr;

    this->rotate = new TransformRotateAround(pivotAxis, 0, pivotPosition);
    this->translate = new TransformTranslate(pivotPosition + startingRelativePosition);

    TransformComposite* composite = new TransformComposite();
    composite->addTransform(transform);
    composite->addTransform(this->translate);
    composite->addTransform(this->rotate);

    this->transformation = composite;

    Application::getInstance()->registerObserver(this);
}

OrbittingObject::OrbittingObject(Model *model, ShaderProgram *shaderProgram, Transform* transform, glm::vec3 pivotAxis, float rotationRate, OrbittingObject *pivotObject, glm::vec3 startingRelativePosition, Material material)
    : OrbittingObject(model, shaderProgram, transform, pivotAxis, rotationRate, pivotObject->getPosition(), startingRelativePosition, material)
{
    this->pivotObject = pivotObject;
}

OrbittingObject::~OrbittingObject()
{
    Application::getInstance()->registerObserver(this);
}



void OrbittingObject::setCurrentTransform(float timeSinceLastFrameSec)
{
    this->rotate->setRotationAngle(this->rotate->getRotationAngle() + this->rotationRate * timeSinceLastFrameSec);
    
    if(this->pivotObject != nullptr)
    {
        glm::vec4 pivotObjectPos = this->pivotObject->getPosition();

        this->rotate->setPivotPoint(pivotObjectPos);

        this->translate->translationVector = pivotObjectPos + this->startingRelativePosition;
    }
}



glm::vec4 OrbittingObject::getPosition()
{
    return this->transformation->getMatrix() * glm::vec4(0, 0, 0, 1);
}



void OrbittingObject::notify(const Event * event)
{
    switch(event->eventType)
    {
        case EVENT_FRAME:
            const FrameEventData* frameEvent = static_cast<const FrameEventData*>(event->data);
            this->frameHandler(frameEvent->timeSinceLastFrameSec);
            break;
    }
}

void OrbittingObject::frameHandler(double timeSinceLastFrameSec)
{
    this->setCurrentTransform(timeSinceLastFrameSec);
}
