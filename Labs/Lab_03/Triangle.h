#pragma once

#include "Shape.h"



class Triangle : public DrawableObject
{
public:
	Triangle(VAO* vao, ShaderProgram* shaderProgram);

	virtual void draw() override;
};

