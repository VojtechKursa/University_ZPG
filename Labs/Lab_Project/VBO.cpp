#include "VBO.h"

VBO::VBO()
{
	this->vboId = 0;

	glGenBuffers(1, &this->vboId);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &this->vboId);
}



void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void VBO::buffer(const float* array, int length)
{
	this->bind();

	glBufferData(GL_ARRAY_BUFFER, length, array, GL_STATIC_DRAW);
}
