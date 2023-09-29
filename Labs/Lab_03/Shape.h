#pragma once

#include "VAO.h"
#include "ShaderProgram.h"

class Shape
{
protected:
	VAO* vao;
	ShaderProgram* shaderProgram;

	Shape();
	Shape(VAO* vao, ShaderProgram* shaderProgram);

public:
	virtual ~Shape();
	virtual void draw();
};

