#include "ShaderProgram.h"

#include <stdio.h>
#include <stdlib.h>

#include "Application.h"
#include "Light.h"



ShaderProgram::ShaderProgram()
{
	this->programId = glCreateProgram();

	this->camera = Application::getInstance()->getRenderer()->getCamera();

	this->camera->registerViewMatrixChangedObserver(this);
	this->camera->registerProjectionMatrixChangedObserver(this);
}

ShaderProgram::~ShaderProgram()
{
	for (auto shader : this->shaders)
	{
		shader->detachFromProgram(this->programId);
	}

	glDeleteProgram(this->programId);

	this->camera->unregisterViewMatrixChangedObserver(this);
	this->camera->unregisterProjectionMatrixChangedObserver(this);
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

	this->bindUniform("viewMatrix", this->camera->getViewMatrix());
	this->bindUniform("projectionMatrix", this->camera->getProjectionMatrix());
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

		fprintf(stderr, "Shader program linker failure: %s\n", strInfoLog);

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



bool ShaderProgram::bindUniform(const char *uniformName, float value)
{
	this->use();

	GLint uniformId = glGetUniformLocation(this->programId, uniformName);

	if (uniformId != -1)
	{
		glUniform1f(uniformId, value);
	}

	this->unuse();

	return uniformId != -1;
}

bool ShaderProgram::bindUniform(const char *uniformName, glm::vec3 vec)
{
	this->use();

	GLint uniformId = glGetUniformLocation(this->programId, uniformName);

	if (uniformId != -1)
	{
		glUniform3fv(uniformId, 1, &vec[0]);
	}

	this->unuse();

	return uniformId != -1;
}

bool ShaderProgram::bindUniform(const char *uniformName, glm::vec4 vec)
{
    this->use();

	GLint uniformId = glGetUniformLocation(this->programId, uniformName);

	if (uniformId != -1)
	{
		glUniform4fv(uniformId, 1, &vec[0]);
	}

	this->unuse();

	return uniformId != -1;
}

bool ShaderProgram::bindUniform(const char* uniformName, glm::mat3 matrix)
{
	this->use();

	GLint uniformId = glGetUniformLocation(this->programId, uniformName);

	if (uniformId != -1)
	{
		glUniformMatrix3fv(uniformId, 1, GL_FALSE, &matrix[0][0]);
	}

	this->unuse();

	return uniformId != -1;
}

bool ShaderProgram::bindUniform(const char *uniformName, glm::mat4 matrix)
{
	this->use();
	
	GLint uniformId = glGetUniformLocation(this->programId, uniformName);
	
	if(uniformId != -1)
	{
		glUniformMatrix4fv(uniformId, 1, GL_FALSE, &matrix[0][0]);
	}

	this->unuse();

	return uniformId != -1;
}



void ShaderProgram::viewMatrixChangedHandler(glm::mat4 newMatrix, glm::vec3 newPosition)
{
	this->bindUniform("viewMatrix", newMatrix);
	this->bindUniform("cameraPosWorld", newPosition);
}

void ShaderProgram::projectionMatrixChangedHandler(glm::mat4 newMatrix)
{
	this->bindUniform("projectionMatrix", newMatrix);
}

void ShaderProgram::lightChangedHandler(Light* light)
{
	this->bindUniform("lightPosition", light->getPosition());
	this->bindUniform("lightColor", light->getLightColor());
}
