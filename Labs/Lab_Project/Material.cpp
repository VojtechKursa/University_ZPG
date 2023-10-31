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

    if (program->bindUniform("objColor", this->color))
        result |= COLOR;
    else if (program->bindUniform("objColor3", glm::vec3(this->color / this->color.w)))
        result |= COLOR;

    return result;
}
