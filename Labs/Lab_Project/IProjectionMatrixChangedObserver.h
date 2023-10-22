#pragma once

#include <glm/mat4x4.hpp>

class IProjectionMatrixChangedObserver
{
public:
	virtual void projectionMatrixChangedHandler(glm::mat4 newMatrix) = 0;
};