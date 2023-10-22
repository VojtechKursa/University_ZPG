#pragma once

#include "TransformComposite.h"
#include "TransformRotateSimple.h"
#include "../Rotation.h"



class TransformRotate : public TransformComposite
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
};

