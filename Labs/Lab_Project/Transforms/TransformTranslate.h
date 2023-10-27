#pragma once

#include "Transform.h"
#include "../Interfaces/ITransformContinuousable.h"



class TransformTranslate : public Transform, public ITransformContinuousable
{
public:
    glm::vec3 translationVector;

    TransformTranslate();
    TransformTranslate(glm::vec3 translationVector);
    TransformTranslate(float shiftX, float shiftY, float shiftZ);

    virtual glm::mat4 getMatrix() override;
    virtual void increaseTransformParameter(glm::vec3 increase) override;
};
