#pragma once

#include "TransformTranslate.h"

#include "../Curves/CurveOverflowBehaviour.h"
#include "../Interfaces/ICurve.h"
#include "../Interfaces/IObserver.h"
#include "../Application.h"



class TransformTranslateCurve : public TransformTranslate, public IObserver
{
private:
    ICurve* curve;
    float tSpeed;
    CurveOverflowBehaviour overflow;

    float t = 0;
    int directionModifier = 1;

public:
    TransformTranslateCurve();
    TransformTranslateCurve(ICurve* curve, float tSpeed = -1, CurveOverflowBehaviour overflowBehaviour = OVERFLOW_REVERSE);
    virtual ~TransformTranslateCurve() override;

    virtual void notify(const Event* event) override;
};
