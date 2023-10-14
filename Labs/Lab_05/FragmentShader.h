#pragma once

#include "Shader.h"

class FragmentShader : public Shader
{
public:
	FragmentShader(const char* code) : Shader(GL_FRAGMENT_SHADER, code) { }
};

