#pragma once

#include "Transform.h"
#include "TransformRotateSimple.h"
#include "Rotation.h"



class TransformRotate : public Transform
{
private:
    TransformRotateSimple* yawRotate;
    TransformRotateSimple* pitchRotate;
    TransformRotateSimple* rollRotate;

public:
    TransformRotate();
    TransformRotate(Rotation rotation);
    virtual ~TransformRotate() override;

    virtual glm::mat4 getMatrix() override;

    Rotation getRotation();
    void setRotation(Rotation rotation);
};

