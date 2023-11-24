#include "Material.h"

#include "MaterialSetFlag.h"



Material::Material()
    : Material(glm::vec4(0.385, 0.647, 0.812, 1.0), 1, 1, 2)
{ }

Material::Material(glm::vec3 color)
    : Material(glm::vec4(color, 1.f))
{ }

Material::Material(glm::vec4 color)
    : Material(color, 1, 1, 2)
{ }

Material::Material(glm::vec4 color, float ambient, float diffuse, float specular, float shininessConstant)
{
    this->color = color;

    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;

    this->shininessConstant = shininessConstant;
    this->texture = nullptr;
}

Material::Material(Texture *texture)
    : Material(texture, 1, 1, 2)
{ }

Material::Material(Texture *texture, float ambient, float diffuse, float specular, float shininessConstant)
{
    this->color = glm::vec4(0);

    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;

    this->shininessConstant = shininessConstant;

    this->texture = texture;
}



int Material::setToShader(ShaderProgram *program)
{
    if(program == nullptr)
        return 0;

    int result = 0;

    if (program->bindUniform("ambientCoeficient", this->ambient))
        result |= COEF_AMBIENT;

    if (program->bindUniform("diffusionCoeficient", this->diffuse))
        result |= COEF_DIFFUSE;

    if (program->bindUniform("specularCoeficient", this->specular))
        result |= COEF_SPECULAR;

    if (program->bindUniform("shininessConstant", this->shininessConstant))
        result |= SHININESS_CONST;

    if(texture != nullptr)
    {
        if(texture->bindToProgram(program))
            result |= TEXTURE;
    }
    else
    {
        if (program->bindUniform("objColor", this->color))
            result |= COLOR;
        else if (program->bindUniform("objColor3", glm::vec3(this->color / this->color.w)))
            result |= COLOR;
    }



    return result;
}

Texture *Material::getTexture()
{
    return this->texture;
}

bool Material::activateTexture()
{
    if(this->texture != nullptr)
    {
        this->texture->activate();
        return true;
    }
    else
        return false;
}



bool Material::activateHighlightColor(ShaderProgram* program)
{
    return program->bindUniform("highlightColor", this->highlightColor);
}

bool Material::deactivateHighlightColor(ShaderProgram* program)
{
    return program->bindUniform("highlightColor", glm::vec3(0,0,0));
}
