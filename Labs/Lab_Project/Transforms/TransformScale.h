#pragma once

#include "Transform.h"
#include "../Interfaces/ITransformContinuousable.h"



class TransformScale : public Transform, public ITransformContinuousable
{
public:
    glm::vec3 scalingVector;

    TransformScale();
    TransformScale(glm::vec3 scalingVector);
    TransformScale(float scaleX, float scaleY, float scaleZ);
    TransformScale(float scale);

    virtual glm::mat4 getMatrix() override;
    virtual void increaseTransformParameter(glm::vec3 increase) override;
};
