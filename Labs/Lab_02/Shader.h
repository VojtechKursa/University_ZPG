#pragma once

#include <GL/glew.h>

class Shader
{
protected:
	GLuint shaderId;

	Shader(int type, const char* code);

public:
	void attachToProgram(GLuint programId);
};

