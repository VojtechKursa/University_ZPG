#pragma once

#include <GL/glew.h>

class VBO
{
private:
	GLuint vboId;

public:
	VBO();
	~VBO();

	void bind();
	void buffer(const float* array, int length);
};

