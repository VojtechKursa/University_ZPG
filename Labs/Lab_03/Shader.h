#pragma once

#include <GL/glew.h>

class Shader
{
protected:
	GLuint shaderId;

	Shader(int type, const char* code);

public:
	~Shader();

	void attachToProgram(GLuint programId);
	void detachFromProgram(GLuint programId);
};

