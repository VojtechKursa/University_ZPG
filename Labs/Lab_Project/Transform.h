#pragma once

#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>



class Transform
{
public:
    virtual ~Transform();

    virtual glm::mat4 getMatrix() = 0;
};
