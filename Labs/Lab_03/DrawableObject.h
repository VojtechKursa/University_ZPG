#pragma once

#include "VAO.h"
#include "ShaderProgram.h"

class DrawableObject
{
protected:
	ShaderProgram* shaderProgram;

	DrawableObject();
	DrawableObject(VAO* vao, ShaderProgram* shaderProgram);

public:
	virtual ~DrawableObject();
	virtual void draw();
};

