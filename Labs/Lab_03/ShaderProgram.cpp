#include "ShaderProgram.h"

#include <stdio.h>
#include <stdlib.h>



ShaderProgram::ShaderProgram()
{
	this->programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	for (auto shader : this->shaders)
	{
		shader->detachFromProgram(this->programId);
	}

	glDeleteProgram(this->programId);
}

void ShaderProgram::addShader(Shader* shader)
{
	this->shaders.push_back(shader);

	shader->attachToProgram(this->programId);
}

bool ShaderProgram::removeShader(Shader* shader)
{
	int index = -1;
	
	for (int i = 0; i < this->shaders.size(); i++)
	{
		if (this->shaders[i] == shader)
		{
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		this->shaders.erase(this->shaders.begin() + index);
		
		shader->detachFromProgram(this->programId);

		return true;
	}
	else
		return false;
}

void ShaderProgram::link()
{
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

void ShaderProgram::unuse()
{
	glUseProgram(0);
}

bool ShaderProgram::bindMatrix(const char *variableName, glm::mat4 matrix)
{
	this->use();
	
	GLint idModelTransform = glGetUniformLocation(this->programId, "modelMatrix");
	
	if(idModelTransform != -1)
	{
		glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
		return true;
	}
	else
	{
		return false;
	}
}
