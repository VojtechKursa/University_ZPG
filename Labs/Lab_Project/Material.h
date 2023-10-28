#pragma once

#include <glm/vec4.hpp>

#include "ShaderProgram.h"

class Material
{
private:
    glm::vec4 color;

    float ambient;
    float diffuse;
    float specular;

    float shininessConstant;

public:
    Material();
    Material(glm::vec3 color);
    Material(glm::vec4 color);
    Material(glm::vec4 color, float ambient, float diffuse, float specular, float shininessConstant = 32);

    int setToShader(ShaderProgram* program);
};