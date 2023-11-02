#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 position, glm::vec3 direction, float foi, glm::vec3 lightColor, bool movable, Model *model, ShaderProgram *shaderProgram, Transform *transformation)
    : LightSpot(position, direction, foi, lightColor, model, shaderProgram, Material(lightColor), transformation, movable)
{ }

LightSpot::LightSpot(glm::vec3 position, glm::vec3 direction, float foi, glm::vec3 lightColor, Model *model, ShaderProgram *shaderProgram, Material material, Transform *transformation, bool movable)
    : Light(SPOT_LIGHT, position, direction, foi, lightColor, transformation, shaderProgram, model, movable, material)
{ }
