#pragma once

#include <glm/ext.hpp>

typedef struct LightStruct
{
    float lightStrength;
    float constantAttCoeficient;
    float linearAttCoeficient;
    float quadraticAttCoeficient;

    int type;

    glm::vec3 position;
    glm::vec3 direction;

    float edge_cos;    // cosine of the edge angle the light still illuminates

    glm::vec3 lightColor;

    bool disabled;

    LightStruct(int type, glm::vec3 position, glm::vec3 direction, float foi, glm::vec3 lightColor, float lightStrength = 1, float constantAttCoeficient = 1, float linearAttCoeficient = 0.1f, float quadraticAttCoeficient = 0.01f, bool disabled = false)
        : type(type), position(position), direction(direction), edge_cos(glm::cos(glm::radians(foi) / 2)), lightColor(lightColor), lightStrength(lightStrength), constantAttCoeficient(constantAttCoeficient), linearAttCoeficient(linearAttCoeficient), quadraticAttCoeficient(quadraticAttCoeficient), disabled(disabled)
    { }

} LightStruct_t;
