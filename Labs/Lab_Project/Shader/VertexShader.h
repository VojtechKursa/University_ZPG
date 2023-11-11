#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader(const char* code) : Shader(GL_VERTEX_SHADER, code) { }
};

