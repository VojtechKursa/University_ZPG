#include "Shader.h"

#include <stdio.h>



Shader::Shader(int type, const char* code)
{
	this->shaderId = glCreateShader(type);

	glShaderSource(this->shaderId, 1, &code, nullptr);
	glCompileShader(this->shaderId);

	this->checkStatus();
}

Shader::~Shader()
{
	glDeleteShader(this->shaderId);
}



bool Shader::checkStatus()
{
	GLint status;
	glGetProgramiv(this->shaderId, GL_COMPILE_STATUS, &status);
	
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[static_cast<size_t>(infoLogLength) + 1];
		glGetProgramInfoLog(this->shaderId, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Shader compiler failure: %s\n", strInfoLog);

		delete[] strInfoLog;
	}

	return status != GL_FALSE;
}



void Shader::attachToProgram(GLuint programId)
{
	glAttachShader(programId, this->shaderId);
}

void Shader::detachFromProgram(GLuint programId)
{
	glDetachShader(programId, this->shaderId);
}
