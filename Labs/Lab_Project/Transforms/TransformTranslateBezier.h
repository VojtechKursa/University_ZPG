#pragma once

#include "TransformTranslate.h"

#include "../Curves/BezierCurve.h"
#include "../Curves/BezierOverflowBehaviour.h"
#include "../Interfaces/IObserver.h"
#include "../Application.h"



class TransformTranslateBezier : public TransformTranslate, public IObserver
{
private:
    BezierCurve bezier;
    float tSpeed;
    BezierOverflowBehaviour overflow;

    float t = 0;
    int directionModifier = 1;

public:
    TransformTranslateBezier();
    TransformTranslateBezier(BezierCurve bezier, float tSpeed = -1, BezierOverflowBehaviour overflowBehaviour = OVERFLOW_REVERSE);
    virtual ~TransformTranslateBezier() override;

    virtual void notify(const Event* event) override;
};
