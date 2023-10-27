#pragma once

#include "ITransform.h"



class ITransformContinuousable : public ITransform
{
public:
    virtual void increaseTransformParameter(glm::vec3 increase) = 0;
};