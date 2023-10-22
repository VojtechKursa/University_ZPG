#include "DrawableObject.h"

#include "Transforms/TransformTranslate.h"



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
		glm::mat4 modelMatrix = this->transformation->getMatrix();
		glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));

		this->shaderProgram->bindUniform("modelMatrix", modelMatrix);
		this->shaderProgram->bindUniform("normalMatrix", normalMatrix);
		this->shaderProgram->use();
		
		this->model->draw();
	}
}
