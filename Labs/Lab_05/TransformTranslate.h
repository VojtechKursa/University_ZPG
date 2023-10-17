#pragma once

#include "Transform.h"



class TransformTranslate : public Transform
{
public:
    glm::vec3 translationVector;

    TransformTranslate();
    TransformTranslate(glm::vec3 translationVector);
    TransformTranslate(float shiftX, float shiftY, float shiftZ);

    virtual glm::mat4 getMatrix() override;
};
