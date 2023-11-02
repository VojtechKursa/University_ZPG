#pragma once

#include "Light.h"
#include "../Transforms/TransformModel.h"



class LightPoint : public Light
{
public:
    LightPoint(glm::vec3 position, glm::vec3 lightColor, bool movable = false, Model* model = nullptr, ShaderProgram* shaderProgram = nullptr, Transform* transformation = new TransformModel());
    LightPoint(glm::vec3 position, glm::vec3 lightColor, Model* model, ShaderProgram* shaderProgram, Material material, Transform* transformation = new TransformModel(), bool movable = false);
};