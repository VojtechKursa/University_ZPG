#pragma once

#include "Shape.h"



class Triangle : public Shape
{
public:
	Triangle(VAO* vao, ShaderProgram* shaderProgram);

	virtual void draw() override;
};

