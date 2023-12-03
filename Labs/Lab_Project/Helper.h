#pragma once

#include <glm/ext.hpp>

#include "Rotation.h"

class Helper
{
public:
    static int random(int min, int max);

    static glm::vec3 convertRotation(Rotation rotation);
    static glm::vec3 convertRotation(float pitch, float yaw);

    static glm::vec3 convertColor(glm::vec3 color, bool toFloat);
};
