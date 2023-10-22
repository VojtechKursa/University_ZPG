#pragma once

#include "ShaderProgram.h"
#include "Model.h"
#include "Transforms/Transform.h"

#include "Rotation.h"



class DrawableObject
{
protected:
	ShaderProgram* shaderProgram;
	Model* model;
	Transform* transformation;

public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);
	DrawableObject(Model* model, ShaderProgram* shaderProgram, Transform* transformation);

	virtual void draw();
};

