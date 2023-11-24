#pragma once

#include "Shader/ShaderProgram.h"
#include "Model/Model.h"
#include "Transforms/Transform.h"
#include "Material.h"



class DrawableObject
{
private:
	static DrawableObject** initClickableObjects();
	static void deleteClickableObjects();

protected:
	static const int maxClickableObjects = 255;

	static int nextClickableId;
	static DrawableObject** clickableObjects;

	int clickableId;

	ShaderProgram* shaderProgram;
	Model* model;
	Transform* transformation;
	Material material;

	DrawableObject();

public:
	DrawableObject(Model* model, ShaderProgram* shaderProgram, Material material = Material(), bool clickable = false);
	DrawableObject(Model* model, ShaderProgram* shaderProgram, Transform* transformation, Material material = Material(), bool clickable = false);
	virtual ~DrawableObject();

	bool isClickable();
	int getClickableId();
	static DrawableObject* getClickableObject(int clickableObjectId);

	void select();
	void unselect();

	virtual void draw();
};

