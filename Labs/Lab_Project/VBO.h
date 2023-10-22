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
	static void unbind();

	void buffer(const float* array, int length);
};

