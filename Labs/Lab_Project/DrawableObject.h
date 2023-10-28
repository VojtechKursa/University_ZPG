#pragma once

#include "ShaderProgram.h"
#include "Model.h"
#include "Transforms/Transform.h"
#include "Material.h"



class DrawableObject
{
protected:
	ShaderProgram* shaderProgram;
	Model* model;
	Transform* transformation;
	Material material;

public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram, Material material = Material());
	DrawableObject(Model* model, ShaderProgram* shaderProgram, Transform* transformation, Material material = Material());

	virtual void draw();
};

