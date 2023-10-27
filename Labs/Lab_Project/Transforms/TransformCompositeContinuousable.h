#pragma once

#include "TransformComposite.h"
#include "../Interfaces/ITransformContinuousable.h"



class TransformCompositeContinuousable : public TransformComposite, public ITransformContinuousable
{
public:
    virtual glm::mat4 getMatrix() override;
};