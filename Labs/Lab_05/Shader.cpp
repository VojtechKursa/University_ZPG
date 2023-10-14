#include "Shader.h"

Shader::Shader(int type, const char* code)
{
	this->shaderId = glCreateShader(type);

	glShaderSource(this->shaderId, 1, &code, nullptr);
	glCompileShader(this->shaderId);
}

Shader::~Shader()
{
	glDeleteShader(this->shaderId);
}

void Shader::attachToProgram(GLuint programId)
{
	glAttachShader(programId, this->shaderId);
}

void Shader::detachFromProgram(GLuint programId)
{
	glDetachShader(programId, this->shaderId);
}
