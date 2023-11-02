#include "ShaderProgram.h"

#include <stdio.h>
#include <stdlib.h>

#include "Application.h"
#include "Lights/Light.h"

#include "Events/CameraEventData.h"
#include "Events/MatrixEventData.h"
#include "Events/LightEventData.h"
#include "Events/LightCountEventData.h"



ShaderProgram::ShaderProgram(bool registerToCamera, bool registerToLights)
{
	this->programId = glCreateProgram();

	this->registeredToCamera = registerToCamera;
	this->registeredToLights = registerToLights;

	this->camera = Application::getInstance()->getRenderer()->getCamera();
}

ShaderProgram::~ShaderProgram()
{
	if(this->registeredToCamera)
		this->camera->unregisterObserver(this);

	if(this->registeredToLights)
	{
		Renderer* renderer = Application::getInstance()->getRenderer();

		for (auto light : renderer->getLights())
		{
			light->unregisterObserver(this);
		}

		renderer->unregisterObserver(this);
	}


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

	this->bindUniform("viewMatrix", this->camera->getViewMatrix());
	this->bindUniform("projectionMatrix", this->camera->getProjectionMatrix());

	if(this->registeredToCamera)
	{
		this->camera = Application::getInstance()->getRenderer()->getCamera();
		this->camera->registerObserver(this);
	}

	if(this->registeredToLights)
	{
		Renderer* renderer = Application::getInstance()->getRenderer();
		std::vector<Light*> lights = renderer->getLights();
		Light* light;

		for (int i = 0; i < lights.size(); i++)
		{
			light = lights[i];

			light->registerObserver(this);
			this->bindUniform("lights", light->getLightStruct(), i);
		}

		this->bindUniform("lightCount", static_cast<int>(lights.size()));

		renderer->registerObserver(this);
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

bool ShaderProgram::bindUniform(const char *uniformName, int value)
{
    this->use();

	GLint uniformId = glGetUniformLocation(this->programId, uniformName);

	if (uniformId != -1)
	{
		glUniform1i(uniformId, value);
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

bool ShaderProgram::bindUniform(const char *uniformName, Light *light)
{
	int index = light->getLightIndex();
	LightStruct_t lightStruct = light->getLightStruct();

	return this->bindUniform(uniformName, lightStruct, index);
}

bool ShaderProgram::bindUniform(const char *uniformName, LightStruct_t light, int index)
{
	if(index < 0)
		return false;

	this->use();

	
	char nameBuffer[256];

	sprintf(nameBuffer, "%s[%d].type", uniformName, index);
	GLint uniformId = glGetUniformLocation(this->programId, nameBuffer);
	glUniform1i(glGetUniformLocation(this->programId, nameBuffer), light.type);

	sprintf(nameBuffer, "%s[%d].position", uniformName, index);
	glUniform3fv(glGetUniformLocation(this->programId, nameBuffer), 1, &light.position[0]);
	sprintf(nameBuffer, "%s[%d].direction", uniformName, index);
	glUniform3fv(glGetUniformLocation(this->programId, nameBuffer), 1, &light.direction[0]);
	sprintf(nameBuffer, "%s[%d].foi", uniformName, index);
	glUniform1f(glGetUniformLocation(this->programId, nameBuffer), light.foi);

	sprintf(nameBuffer, "%s[%d].lightColor", uniformName, index);
	glUniform3fv(glGetUniformLocation(this->programId, nameBuffer), 1, &light.lightColor[0]);

	sprintf(nameBuffer, "%s[%d].lightStrength", uniformName, index);
	glUniform1f(glGetUniformLocation(this->programId, nameBuffer), light.lightStrength);
	
	sprintf(nameBuffer, "%s[%d].constantAttCoeficient", uniformName, index);
	glUniform1f(glGetUniformLocation(this->programId, nameBuffer), light.constantAttCoeficient);
	sprintf(nameBuffer, "%s[%d].linearAttCoeficient", uniformName, index);
	glUniform1f(glGetUniformLocation(this->programId, nameBuffer), light.linearAttCoeficient);
	sprintf(nameBuffer, "%s[%d].quadraticAttCoeficient", uniformName, index);
	glUniform1f(glGetUniformLocation(this->programId, nameBuffer), light.quadraticAttCoeficient);

	sprintf(nameBuffer, "%s[%d].disabled", uniformName, index);
	glUniform1i(glGetUniformLocation(this->programId, nameBuffer), light.disabled);
	

	this->unuse();

	return uniformId != -1;
}

void ShaderProgram::notify(const Event *event)
{
	switch(event->eventType)
	{
		case EVENT_CAMERA:
		{
			const CameraEventData* data = static_cast<const CameraEventData*>(event->data);
			this->viewMatrixChangedHandler(data->matrix, data->cameraPosition);
			break;
		}
		case EVENT_PROJECTION_MATRIX:
		{
			const MatrixEventData* data = static_cast<const MatrixEventData*>(event->data);
			this->projectionMatrixChangedHandler(data->matrix);
			break;
		}
		case EVENT_LIGHT:
		{
			const LightEventData* data = static_cast<const LightEventData*>(event->data);
			this->lightChangedHandler(data->light);
			break;
		}
		case EVENT_LIGHT_COUNT:
		{
			const LightCountEventData* data = static_cast<const LightCountEventData*>(event->data);
			this->lightCountChangedHandler(data->added, data->index, data->light, data->lightStruct);
			break;
		}
	}
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
	this->bindUniform("lights", light);
}

void ShaderProgram::lightCountChangedHandler(bool added, int index, Light* light, LightStruct_t lightStruct)
{
	if(added)
	{
		this->bindUniform("lights", lightStruct, index);
		this->bindUniform("lightCount", index + 1);

		light->registerObserver(this);
	}
}
