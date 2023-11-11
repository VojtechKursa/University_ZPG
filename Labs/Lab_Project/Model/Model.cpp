#include "Model.h"

Model::Model(VAO *vao, int vertexCount, int firstVertex, GLenum drawingMode)
{
	this->vao = vao;

	this->vertexCount = vertexCount;
	this->firstVertex = firstVertex;
	this->drawingMode = drawingMode;
}

Model::~Model()
{
	if(this->vao != nullptr)
	{
		delete this->vao;
		this->vao = nullptr;
	}
}

void Model::bind()
{
	this->vao->bind();
}

void Model::unbind()
{
	VAO::unbind();
}

void Model::draw()
{
	this->bind();
	
	glDrawArrays(this->drawingMode, this->firstVertex, this->vertexCount);
}
