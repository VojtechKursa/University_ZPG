#pragma once

#include <glm/ext.hpp>

#include <string>

#include "Rotation.h"



struct ObjectProperties
{
    glm::vec3 position = glm::vec3(0);
    Rotation rotation = Rotation();
    glm::vec3 scale = glm::vec3(1);
    std::string modelName = "sphere";
    std::string vertexShaderName = "vert_default_colorPass4";
    std::string fragmentShaderName = "frag_colorFromIn4";
    bool bindToLights = false;
    glm::vec3 color = glm::vec3(1,1,1);
};