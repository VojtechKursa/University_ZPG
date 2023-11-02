#pragma once

#include "Light.h"
#include "../Transforms/TransformModel.h"



class LightDirectional : public Light
{
public:
    LightDirectional(glm::vec3 direction, glm::vec3 lightColor, bool movable = false, Model* model = nullptr, ShaderProgram* shaderProgram = nullptr, Transform* transformation = new TransformModel());
    LightDirectional(glm::vec3 direction, glm::vec3 lightColor, Model* model, ShaderProgram* shaderProgram, Material material, Transform* transformation = new TransformModel(), bool movable = false);
};