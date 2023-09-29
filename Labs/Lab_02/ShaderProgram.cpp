#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	this->programId = glCreateProgram();
}

void ShaderProgram::addShader(Shader* shader)
{
	this->shaders.push_back(shader);
}

void ShaderProgram::link()
{
	for (auto shader : this->shaders)
	{
		shader->attachToProgram(this->programId);
	}

	glLinkProgram(this->programId);

	if (!this->checkStatus())
	{
		exit(EXIT_FAILURE);
	}
}

bool ShaderProgram::checkStatus()
{
	GLint status;
	glGetProgramiv(this->programId, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->programId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->programId, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Linker failure: %s\n", strInfoLog);

		delete[] strInfoLog;
	}

	return status != GL_FALSE;
}

void ShaderProgram::use()
{
	glUseProgram(this->programId);
}
