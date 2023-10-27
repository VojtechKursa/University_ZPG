#pragma once

#include <glm/mat4x4.hpp>



class ITransform
{
public:
    virtual glm::mat4 getMatrix() = 0;
};