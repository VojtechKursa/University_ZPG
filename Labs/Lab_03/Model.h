#pragma once

#include "Transformation.h"
#include "VAO.h"

class Model
{
private:
	Transformation* transformation;
	VAO* vao;

public:
	void bind();
};

