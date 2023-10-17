#pragma once

#include <glm/mat4x4.hpp>

class IViewMatrixChangedObserver
{
public:
	virtual void viewMatrixChangedHandler(glm::mat4 newMatrix, glm::vec3 newPosition) = 0;
};