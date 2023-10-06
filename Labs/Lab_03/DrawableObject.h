#pragma once

#include "ShaderProgram.h"
#include "Model.h"
#include "TransformModel.h"

#include "Rotation.h"



class DrawableObject
{
protected:
	ShaderProgram* shaderProgram;
	Model* model;
	TransformModel* transformation;

public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram);
	DrawableObject(Model* model, ShaderProgram* shaderProgram, TransformModel* transformation);

	glm::vec3 getPosition();
	Rotation getRotation();
	glm::vec3 getScale();

	void setPosition(glm::vec3 newPosition);
	void setRotation(Rotation newRotation);
	void setScale(glm::vec3 newScale);

	void draw();
};

