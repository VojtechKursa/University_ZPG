#pragma once

#include "Shape.h"



class Rectangle : public Shape
{
public:
	Rectangle(VAO* vao, ShaderProgram* shaderProgram);

	virtual void draw() override;
};
