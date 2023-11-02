#include "Helper.h"

#include <stdlib.h>



int Helper::random(int min, int max)
{
    return (rand() % (max - min) + min);
}

glm::vec3 Helper::convertRotation(Rotation rotation)
{
    return Helper::convertRotation(rotation.pitch, rotation.yaw);
}

glm::vec3 Helper::convertRotation(float pitch, float yaw)
{
    float pitchRad = glm::radians(pitch);
	float yawRad = glm::radians(yaw);

	float x = sin(pitchRad) * cos(yawRad);
	float z = sin(pitchRad) * sin(yawRad);
	float y = cos(pitchRad);

    return glm::vec3(x,y,z);
}