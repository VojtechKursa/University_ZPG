#pragma once

#include <glm/mat4x4.hpp>

#include <vector>

#include "../Subject.h"
#include "Shader.h"
#include "../Camera.h"
#include "../Lights/LightStruct.h"

class Light;



class ShaderProgram : public Subject, public IObserver
{
private:
	GLuint programId;
	std::vector<Shader*> shaders;
	Camera* camera;

	bool registeredToCamera, registeredToLights;

	void viewMatrixChangedHandler(glm::mat4 newMatrix, glm::vec3 newPosition);
	void projectionMatrixChangedHandler(glm::mat4 newMatrix);
	void lightChangedHandler(Light* light);
	void lightCountChangedHandler(bool added, int index, Light* light, LightStruct_t lightStruct);

public:
	ShaderProgram(bool registerToCamera = true, bool registerToLights = true);
	~ShaderProgram();

	void addShader(Shader* shader);
	bool removeShader(Shader* shader);

	void link();

	bool checkStatus();

	void use();
	static void unuse();

	bool bindUniform(const char* uniformName, float value);
	bool bindUniform(const char* uniformName, int value);
	bool bindUniform(const char* uniformName, glm::vec3 vec);
	bool bindUniform(const char* uniformName, glm::vec4 vec);
	bool bindUniform(const char* uniformName, glm::mat3 matrix);
	bool bindUniform(const char* uniformName, glm::mat4 matrix);
	bool bindUniform(const char* uniformName, Light* light);
	bool bindUniform(const char* uniformName, LightStruct_t light, int index);

	virtual void notify(const Event* event) override;
};

