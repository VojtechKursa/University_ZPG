#pragma once

#include "Shape.h"



class Rectangle : public DrawableObject
{
public:
	Rectangle(VAO* vao, ShaderProgram* shaderProgram);

	virtual void draw() override;
};
