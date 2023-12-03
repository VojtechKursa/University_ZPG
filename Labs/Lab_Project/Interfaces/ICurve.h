#pragma once

#include <glm/vec3.hpp>

class ICurve
{
public:
    virtual glm::vec3 getPoint(float t) = 0;

    virtual size_t getSegmentCount() = 0;
};
