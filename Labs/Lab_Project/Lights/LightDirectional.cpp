#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 direction, glm::vec3 lightColor, bool movable, Model *model, ShaderProgram *shaderProgram, Transform *transformation)
    : LightDirectional(direction, lightColor, model, shaderProgram, Material(lightColor), transformation, movable)
{ }

LightDirectional::LightDirectional(glm::vec3 direction, glm::vec3 lightColor, Model *model, ShaderProgram *shaderProgram, Material material, Transform *transformation, bool movable)
    : Light(DIRECTIONAL_LIGHT, glm::vec3(0), direction, 360, lightColor, transformation, shaderProgram, model, movable, material)
{ }
