#include "LightPoint.h"



LightPoint::LightPoint(glm::vec3 position, glm::vec3 lightColor, bool movable, Model *model, ShaderProgram *shaderProgram, Transform *transformation)
    : LightPoint(position, lightColor, model, shaderProgram, Material(lightColor), transformation, movable)
{ }

LightPoint::LightPoint(glm::vec3 position, glm::vec3 lightColor, Model *model, ShaderProgram *shaderProgram, Material material, Transform *transformation, bool movable)
    : Light(POINT_LIGHT, position, glm::vec3(0), 360, lightColor, transformation, shaderProgram, model, movable, material)
{ }
