#pragma once

#include <glm/vec3.hpp>

typedef struct LightStruct
{
    float lightStrength;
    float constantAttCoeficient;
    float linearAttCoeficient;
    float quadraticAttCoeficient;

    int type;

    glm::vec3 position;
    glm::vec3 direction;

    glm::vec3 lightColor;

    LightStruct(int type, glm::vec3 position, glm::vec3 direction, glm::vec3 lightColor, float lightStrength = 1, float constantAttCoeficient = 1, float linearAttCoeficient = 0.1f, float quadraticAttCoeficient = 0.01f)
        : type(type), position(position), direction(direction), lightColor(lightColor), lightStrength(lightStrength), constantAttCoeficient(constantAttCoeficient), linearAttCoeficient(linearAttCoeficient), quadraticAttCoeficient(quadraticAttCoeficient)
    { }
} LightStruct_t;
