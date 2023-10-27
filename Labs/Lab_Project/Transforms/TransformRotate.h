#pragma once

#include "TransformCompositeContinuousable.h"
#include "TransformRotateSimple.h"
#include "../Rotation.h"



class TransformRotate : public TransformCompositeContinuousable
{
private:
    TransformRotateSimple* yawRotate;
    TransformRotateSimple* pitchRotate;
    TransformRotateSimple* rollRotate;

public:
    TransformRotate();
    TransformRotate(Rotation rotation);

    Rotation getRotation();
    void setRotation(Rotation rotation);

    virtual void increaseTransformParameter(glm::vec3 increase) override;
};

