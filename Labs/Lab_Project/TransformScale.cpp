#include "TransformScale.h"



TransformScale::TransformScale()
    : TransformScale(glm::vec3(1,1,1))
{ }

TransformScale::TransformScale(glm::vec3 scalingVector)
{
    this->scalingVector = scalingVector;
}

TransformScale::TransformScale(float scaleX, float scaleY, float scaleZ)
    : TransformScale(glm::vec3(scaleX, scaleY, scaleZ))
{ }

TransformScale::TransformScale(float scale)
    : TransformScale(glm::vec3(scale, scale, scale))
{ }



glm::mat4 TransformScale::getMatrix()
{
    return glm::scale(glm::identity<glm::mat4>(), this->scalingVector);
}
