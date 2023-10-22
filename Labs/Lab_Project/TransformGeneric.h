#pragma once

#include "Transform.h"



class TransformGeneric : public Transform
{
public:
    glm::mat4 matrix;

    TransformGeneric();
    TransformGeneric(glm::mat4 matrix);

    virtual glm::mat4 getMatrix() override;
};
