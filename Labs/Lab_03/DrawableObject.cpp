#include "DrawableObject.h"



DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram)
	: DrawableObject(model, shaderProgram, new TransformModel())
{ }

DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram, TransformModel *transformation)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->transformation = transformation;
}



glm::vec3 DrawableObject::getPosition()
{
	return this->transformation->getPosition();
}

Rotation DrawableObject::getRotation()
{
	return this->transformation->getRotation();
}

glm::vec3 DrawableObject::getScale()
{
	return this->transformation->getScale();
}



void DrawableObject::setPosition(glm::vec3 newPosition)
{
	this->transformation->setPosition(newPosition);
}

void DrawableObject::setRotation(Rotation newRotation)
{
	this->transformation->setRotation(newRotation);
}

void DrawableObject::setScale(glm::vec3 newScale)
{
	this->transformation->setScale(newScale);
}



void DrawableObject::draw()
{
	this->shaderProgram->bindMatrix("modelMatrix", this->transformation->getMatrix());
	this->shaderProgram->use();
	
	this->model->draw();
}
