#include "TransformRotate.h"



TransformRotate::TransformRotate()
    : TransformRotate(Rotation(0,0,0))
{ }

TransformRotate::TransformRotate(Rotation rotation)
{
    this->yawRotate = new TransformRotateSimple(glm::vec3(0,1,0), rotation.yaw);
    this->pitchRotate = new TransformRotateSimple(glm::vec3(1,0,0), rotation.pitch);
    this->rollRotate = new TransformRotateSimple(glm::vec3(0,0,-1), rotation.roll);

    addTransform(this->yawRotate);
    addTransform(this->pitchRotate);
    addTransform(this->rollRotate);
}



Rotation TransformRotate::getRotation()
{
    return Rotation(this->yawRotate->rotationAngle, this->pitchRotate->rotationAngle, this->rollRotate->rotationAngle);
}

void TransformRotate::setRotation(Rotation rotation)
{
    this->yawRotate->rotationAngle = rotation.yaw;
    this->pitchRotate->rotationAngle = rotation.pitch;
    this->rollRotate->rotationAngle = rotation.roll;
}
