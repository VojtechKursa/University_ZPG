#include "DrawableObject.h"

#include "Transforms/TransformTranslate.h"



int DrawableObject::nextClickableId = 1;	// skip 0 because 0 means "no object"
DrawableObject** DrawableObject::clickableObjects = DrawableObject::initClickableObjects();



DrawableObject** DrawableObject::initClickableObjects()
{
	size_t totalLength = static_cast<size_t>(DrawableObject::maxClickableObjects) + 1;

	DrawableObject** result = new DrawableObject* [totalLength];

	memset(result, 0, sizeof(result) * totalLength);
	atexit(DrawableObject::deleteClickableObjects);

	return result;
}

void DrawableObject::deleteClickableObjects()
{
	delete[] DrawableObject::clickableObjects;
}



DrawableObject::DrawableObject()
{
	this->clickableId = -1;

	this->model = nullptr;
	this->shaderProgram = nullptr;
	this->transformation = nullptr;
	this->material = Material();
}

DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram, Material material, bool clickable)
	: DrawableObject(model, shaderProgram, new TransformTranslate(), material, clickable)
{ }

DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram, Transform *transformation, Material material, bool clickable)
{
	if (clickable)
	{
		this->clickableId = DrawableObject::nextClickableId++;

		if(this->clickableId <= DrawableObject::maxClickableObjects)
			DrawableObject::clickableObjects[this->clickableId] = this;
	}
	else
		this->clickableId = -1;

	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transformation = transformation;
	this->material = material;

	this->material.setToShader(this->shaderProgram);
}

DrawableObject::~DrawableObject()
{
	if(this->shaderProgram != nullptr)
	{
		delete this->shaderProgram;
		this->shaderProgram = nullptr;
	}

	if(this->transformation != nullptr)
	{
		delete this->transformation;
		this->transformation = nullptr;
	}
}



bool DrawableObject::isClickable()
{
	return this->clickableId > 0 && this->clickableId <= DrawableObject::maxClickableObjects;
}

int DrawableObject::getClickableId()
{
	return this->clickableId;
}

DrawableObject* DrawableObject::getClickableObject(int clickableObjectId)
{
	if (clickableObjectId > 0 && clickableObjectId <= DrawableObject::maxClickableObjects)
		return clickableObjects[clickableObjectId];
	else
		return nullptr;
}



void DrawableObject::select()
{
	this->material.activateHighlightColor(this->shaderProgram);
}

void DrawableObject::unselect()
{
	this->material.deactivateHighlightColor(this->shaderProgram);
}



void DrawableObject::draw()
{
	if(this->model != nullptr && this->shaderProgram != nullptr)
	{
		this->material.activateTexture();

		glm::mat4 modelMatrix;
		if(this->transformation != nullptr)
			modelMatrix = this->transformation->getMatrix();
		else
			modelMatrix = glm::identity<glm::mat4>();
		
		glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

		this->shaderProgram->bindUniform("modelMatrix", modelMatrix);
		this->shaderProgram->bindUniform("normalMatrix", normalMatrix);
		this->shaderProgram->use();
		
		if(this->isClickable())
			glStencilFunc(GL_ALWAYS, this->clickableId, 0xFF);

		this->model->draw();
	}
}
