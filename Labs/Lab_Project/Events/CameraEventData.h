#pragma once

#include <glm/vec3.hpp>

#include "MatrixEventData.h"



class Camera;

class CameraEventData : public MatrixEventData
{
public:
    const glm::vec3 cameraPosition;

    CameraEventData(glm::mat4 viewMatrix, glm::vec3 cameraPosition)
        : MatrixEventData(viewMatrix), cameraPosition(cameraPosition)
    { }
};
