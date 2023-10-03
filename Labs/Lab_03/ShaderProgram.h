#pragma once

#include <glm/mat4x4.hpp>

#include <vector>

#include "Shader.h"



class ShaderProgram
{
private:
	GLuint programId;
	std::vector<Shader*> shaders;

public:
	ShaderProgram();
	~ShaderProgram();

	void addShader(Shader* shader);
	bool removeShader(Shader* shader);

	void link();

	bool checkStatus();

	void use();

	void setTransformMatrix(glm::mat4 matrix);
};

