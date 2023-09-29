#pragma once

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
};

