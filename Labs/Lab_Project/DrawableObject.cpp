#include "DrawableObject.h"

#include "Transforms/TransformTranslate.h"



DrawableObject::DrawableObject()
{
	this->model = nullptr;
	this->shaderProgram = nullptr;
	this->transformation = nullptr;
	this->material = Material();
}

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
	if(this->model != nullptr && this->shaderProgram != nullptr)
	{
		glm::mat4 modelMatrix;
		if(this->transformation != nullptr)
			modelMatrix = this->transformation->getMatrix();
		else
			modelMatrix = glm::identity<glm::mat4>();
		
		glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

		this->shaderProgram->bindUniform("modelMatrix", modelMatrix);
		this->shaderProgram->bindUniform("normalMatrix", normalMatrix);
		this->shaderProgram->use();
		
		this->model->draw();
	}
}
