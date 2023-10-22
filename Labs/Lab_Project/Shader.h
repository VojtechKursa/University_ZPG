#pragma once

#include <GL/glew.h>

class Shader
{
protected:
	GLuint shaderId;

public:
	Shader(int type, const char* code);
	~Shader();

	void attachToProgram(GLuint programId);
	void detachFromProgram(GLuint programId);
};

