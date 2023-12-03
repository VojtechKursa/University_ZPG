#pragma once

#include <vector>

#include "BezierCubic.h"
#include "../Interfaces/ICurve.h"



class BezierCurve : public ICurve
{
private:
    std::vector<BezierCubic> cubics;

public:
    BezierCurve();
    BezierCurve(std::vector<glm::vec3> points);

    virtual glm::vec3 getPoint(float t) override;

    virtual size_t getSegmentCount() override;
};