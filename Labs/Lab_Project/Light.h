#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "Subject.h"
#include "DrawableObject.h"
#include "LightStruct.h"



class Light : public DrawableObject, public Subject, public IObserver
{
private:
	enum LightType { POINT_LIGHT, DIRECTIONAL_LIGHT, SPOT_LIGHT, LIGHT_TYPE_UNDEFINED };

	glm::vec3 motionVector;

	glm::vec3 position;
	glm::vec3 direction;

	LightType lightType;

	glm::vec3 lightColor;
	
	float lightStrength = 1;
    float constantAttCoeficient = 1;
    float linearAttCoeficient = 0.1f;
    float quadraticAttCoeficient = 0.01f;


	int convertLightType(Light::LightType lightType);
	Light::LightType convertLightType(int lightType);

	void frameHandler(double timeSinceLastFrameSec);
	void keyHandler(int key, int scancode, int action, int mods);

public:
	Light(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 lightColor = glm::vec3(1, 1, 1), Transform* transformation = nullptr, ShaderProgram* shaderProgram = nullptr, Model* model = nullptr, bool movable = false);
	Light(glm::vec3 direction, glm::vec3 lightColor = glm::vec3(1, 1, 1), bool movable = false);
	Light(glm::vec3 position, glm::vec3 direction, glm::vec3 lightColor = glm::vec3(1, 1, 1), Transform* transformation = nullptr, ShaderProgram* shaderProgram = nullptr, Model* model = nullptr, bool movable = false);

	glm::vec3 getPosition();
	glm::vec3 getLightColor();
	bool hasModel();

	bool setPosition(glm::vec3 position);
	bool setLightColor(glm::vec3 lightColor);
	void setAttCoeficients(float lightStrength, float constantAttCoeficient, float linearAttCoeficient, float quadraticAttCoeficient);

	int getLightIndex();
	LightStruct_t getLightStruct();


	virtual void notify(const Event* event) override;
};
