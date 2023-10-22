#pragma once

#include <glm/mat4x4.hpp>

#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "Interfaces/IViewMatrixChangedObserver.h"
#include "Interfaces/IProjectionMatrixChangedObserver.h"
#include "Interfaces/ILightObserver.h"

class Light;



class ShaderProgram : public IViewMatrixChangedObserver, public IProjectionMatrixChangedObserver, public ILightObserver
{
private:
	GLuint programId;
	std::vector<Shader*> shaders;
	Camera* camera;

public:
	ShaderProgram();
	~ShaderProgram();

	void addShader(Shader* shader);
	bool removeShader(Shader* shader);

	void link();

	bool checkStatus();

	void use();
	static void unuse();

	bool bindUniform(const char* uniformName, glm::vec3 vec);
	bool bindUniform(const char* uniformName, glm::mat4 matrix);

	virtual void viewMatrixChangedHandler(glm::mat4 newMatrix, glm::vec3 newPosition) override;
	virtual void projectionMatrixChangedHandler(glm::mat4 newMatrix) override;
	virtual void lightChangedHandler(Light* light) override;
};

