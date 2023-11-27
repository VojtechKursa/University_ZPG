#pragma once

#include <vector>

#include "BezierCubic.h"



class BezierCurve
{
private:
    std::vector<BezierCubic> cubics;
    int lastOffset;

public:
    BezierCurve(std::vector<glm::vec3> points);

    glm::vec3 getPoint(float t);
};