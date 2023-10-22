#include "TransformGeneric.h"



TransformGeneric::TransformGeneric()
    : TransformGeneric(glm::identity<glm::mat4>())
{ }

TransformGeneric::TransformGeneric(glm::mat4 matrix)
{
    this->matrix = matrix;
}



glm::mat4 TransformGeneric::getMatrix()
{
    return this->matrix;
}
