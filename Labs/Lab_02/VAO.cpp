#include "VAO.h"



void VAO::addVbo(VBO* vbo)
{
	for (auto x : this->vbos)
	{
		if (x == vbo)
			return;
	}

	vbos.push_back(vbo);
}



VAO::VAO()
{
	this->vaoId = 0;
	glGenVertexArrays(1, &this->vaoId);
}

VAO::~VAO()
{
	for (auto vbo : vbos)
	{
		delete vbo;
	}

	glDeleteVertexArrays(1, &this->vaoId);
}



void VAO::bind()
{
	glBindVertexArray(this->vaoId);
}



void VAO::enableVertexAttributes(VBO* vbo, GLuint attributeIndex, GLint lengthOfData, GLenum dataType, GLboolean normalized, GLsizei shift, size_t beginning)
{
	this->enableVertexAttributes(vbo, attributeIndex, lengthOfData, dataType, normalized, shift, (void*)beginning);
}

void VAO::enableVertexAttributes(VBO* vbo, GLuint attributeIndex, GLint lengthOfData, GLenum dataType, GLboolean normalized, GLsizei shift, const void* beginning)
{
	this->bind();

	glEnableVertexAttribArray(attributeIndex);

	vbo->bind();

	glVertexAttribPointer(attributeIndex, lengthOfData, dataType, normalized, shift, beginning);

	this->addVbo(vbo);
}
