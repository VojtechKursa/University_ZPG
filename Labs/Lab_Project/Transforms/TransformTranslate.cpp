#include "TransformTranslate.h"



TransformTranslate::TransformTranslate()
    : TransformTranslate(glm::vec3(0,0,0))
{ }

TransformTranslate::TransformTranslate(glm::vec3 translationVector)
{
    this->translationVector = translationVector;
}

TransformTranslate::TransformTranslate(float shiftX, float shiftY, float shiftZ)
    : TransformTranslate(glm::vec3(shiftX, shiftY, shiftZ))
{ }



glm::mat4 TransformTranslate::getMatrix()
{
    return glm::translate(glm::identity<glm::mat4>(), this->translationVector);
}

void TransformTranslate::increaseTransformParameter(glm::vec3 increase)
{
    this->translationVector += increase;
}
