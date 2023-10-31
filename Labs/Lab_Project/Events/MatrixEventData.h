#pragma once

#include <glm/mat4x4.hpp>

#include "EventData.h"

class MatrixEventData : public EventData
{
public:
    const glm::mat4 matrix;

    MatrixEventData(glm::mat4 matrix)
        : matrix(matrix)
    { }
};
