#pragma once

#include <glm/ext.hpp>

#include <string>

#include "Rotation.h"
#include "Material.h"



struct ObjectProperties
{
    glm::vec3 position = glm::vec3(0);
    Rotation rotation = Rotation();
    glm::vec3 scale = glm::vec3(1);
    std::string modelName = "sphere";
    std::string vertexShaderName = "vert_default_colorPass4";
    std::string fragmentShaderName = "frag_colorFromIn4";
    bool bindToCamera = true;
    bool bindToLights = false;
    Material material = Material();
    bool clickable = false;
};