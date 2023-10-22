#include "TransformRotateSimple.h"



TransformRotateSimple::TransformRotateSimple()
    : TransformRotateSimple(glm::vec3(0,1,0), 0)
{ }

TransformRotateSimple::TransformRotateSimple(glm::vec3 pivotAxis, float rotationAngle)
{
    this->pivotAxis = pivotAxis;
    this->rotationAngle = rotationAngle;
}

TransformRotateSimple::TransformRotateSimple(float pivotAxisX, float pivotAxisY, float pivotAxisZ, float rotationAngle)
    : TransformRotateSimple(glm::vec3(pivotAxisX, pivotAxisY, pivotAxisZ), rotationAngle)
{ }



glm::mat4 TransformRotateSimple::getMatrix()
{
    return glm::rotate(glm::identity<glm::mat4>(), glm::radians(this->rotationAngle), this->pivotAxis);
}
