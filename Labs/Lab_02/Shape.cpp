#include "Shape.h"

Shape::Shape()
{
	this->vao = nullptr;
	this->shaderProgram = nullptr;
}

Shape::Shape(VAO* vao, ShaderProgram* shaderProgram)
{
	this->vao = vao;
	this->shaderProgram = shaderProgram;
}

void Shape::draw()
{
	this->shaderProgram->use();
	this->vao->bind();
}
