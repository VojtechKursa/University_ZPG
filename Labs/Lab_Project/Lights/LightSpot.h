#pragma once

#include "Light.h"
#include "../Transforms/TransformModel.h"



class LightSpot : public Light
{
public:
    LightSpot(glm::vec3 position, glm::vec3 direction, float foi, glm::vec3 lightColor, bool movable = false, Model* model = nullptr, ShaderProgram* shaderProgram = nullptr, Transform* transformation = new TransformModel());
    LightSpot(glm::vec3 position, glm::vec3 direction, float foi, glm::vec3 lightColor, Model* model, ShaderProgram* shaderProgram, Material material, Transform* transformation = new TransformModel(), bool movable = false);
};