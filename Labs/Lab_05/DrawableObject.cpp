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
	if(this->model != nullptr && this->shaderProgram != nullptr && this->transformation != nullptr)
	{
		this->shaderProgram->bindUniform("modelMatrix", this->transformation->getMatrix());
		this->shaderProgram->use();
		
		this->model->draw();
	}
}
