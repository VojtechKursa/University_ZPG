#pragma once

#include <glm/mat4x4.hpp>

#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "IViewMatrixChangedObserver.h"
#include "IProjectionMatrixChangedObserver.h"



class ShaderProgram : public IViewMatrixChangedObserver, public IProjectionMatrixChangedObserver
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

	bool bindMatrix(const char* variableName, glm::mat4 matrix);

	virtual void viewMatrixChangedHandler(glm::mat4 newMatrix) override;
	virtual void projectionMatrixChangedHandler(glm::mat4 newMatrix) override;
};

