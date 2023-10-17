#include "DrawableObject.h"

#include "TransformTranslate.h"



DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram)
	: DrawableObject(model, shaderProgram, new TransformTranslate())
{ }

DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram, Transform *transformation)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transformation = transformation;
}



void DrawableObject::draw()
{
	this->shaderProgram->bindUniform("modelMatrix", this->transformation->getMatrix());
	this->shaderProgram->use();
	
	if (this->model != nullptr)
	{
		this->model->draw();
	}
}
