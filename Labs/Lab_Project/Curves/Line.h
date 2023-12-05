#pragma once

#include <glm/vec3.hpp>

#include "../Interfaces/ICurve.h"



class Line : public ICurve
{
private:
    const glm::vec3 originPoint;
    const glm::vec3 directionalVector;

public:
    Line(glm::vec3 originPoint, glm::vec3 value2, bool value2IsPoint);

    virtual glm::vec3 getPoint(float t) override;

    virtual size_t getSegmentCount() override { return 1; }
};
