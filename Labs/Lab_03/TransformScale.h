#pragma once

#include "Transform.h"



class TransformScale : public Transform
{
public:
    glm::vec3 scalingVector;

    TransformScale();
    TransformScale(glm::vec3 scalingVector);
    TransformScale(float scaleX, float scaleY, float scaleZ);

    virtual glm::mat4 getMatrix() override;
};
