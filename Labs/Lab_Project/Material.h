#pragma once

#include <glm/vec4.hpp>

#include "ShaderProgram.h"
#include "Texture.h"



class Material
{
private:
    glm::vec4 color;

    float ambient;
    float diffuse;
    float specular;

    float shininessConstant;

    Texture* texture;

public:
    Material();
    Material(glm::vec3 color);
    Material(glm::vec4 color);
    Material(glm::vec4 color, float ambient, float diffuse, float specular, float shininessConstant = 32);
    Material(Texture* texture);
    Material(Texture* texture, float ambient, float diffuse, float specular, float shininessConstant = 32);

    int setToShader(ShaderProgram* program);

    Texture* getTexture();
    bool activateTexture();
};