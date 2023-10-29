#include "DrawableObject.h"

#include "Transforms/TransformTranslate.h"



DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram, Material material)
	: DrawableObject(model, shaderProgram, new TransformTranslate(), material)
{ }

DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram, Transform *transformation, Material material)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transformation = transformation;
	this->material = material;

	this->material.setToShader(this->shaderProgram);
}

DrawableObject::~DrawableObject()
{ }



void DrawableObject::draw()
{
	if(this->model != nullptr && this->shaderProgram != nullptr && this->transformation != nullptr)
	{
		glm::mat4 modelMatrix = this->transformation->getMatrix();
		glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

		this->shaderProgram->bindUniform("modelMatrix", modelMatrix);
		this->shaderProgram->bindUniform("normalMatrix", normalMatrix);
		this->shaderProgram->use();
		
		this->model->draw();
	}
}
