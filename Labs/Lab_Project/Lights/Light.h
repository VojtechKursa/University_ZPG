#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "../Subject.h"
#include "../DrawableObject.h"
#include "LightStruct.h"



class Light : public DrawableObject, public Subject, public IObserver
{
protected:
	enum LightType { POINT_LIGHT, DIRECTIONAL_LIGHT, SPOT_LIGHT, LIGHT_TYPE_UNDEFINED };

	glm::vec3 motionVector;

	glm::vec3 position;
	glm::vec3 direction;

	float foi;

	LightType lightType;

	glm::vec3 lightColor;

	bool movable;

	bool enabled;
	
	float lightStrength = 1;
    float constantAttCoeficient = 1;
    float linearAttCoeficient = 0.1f;
    float quadraticAttCoeficient = 0.01f;


	int convertLightType(Light::LightType lightType);
	Light::LightType convertLightType(int lightType);

	void frameHandler(double timeSinceLastFrameSec);
	void keyHandler(int key, int scancode, int action, int mods);

	Light(Light::LightType type, glm::vec3 position, glm::vec3 direction, float foi, glm::vec3 lightColor, Transform* transformation, ShaderProgram* shaderProgram, Model* model, bool movable);
	Light(Light::LightType type, glm::vec3 position, glm::vec3 direction, float foi, glm::vec3 lightColor, Transform* transformation, ShaderProgram* shaderProgram, Model* model, bool movable, Material material);
	virtual ~Light();

public:
	glm::vec3 getPosition();
	glm::vec3 getLightColor();
	bool hasModel();

	bool setPosition(glm::vec3 position);
	bool setLightColor(glm::vec3 lightColor);
	void setAttCoeficients(float lightStrength, float constantAttCoeficient, float linearAttCoeficient, float quadraticAttCoeficient);

	int getLightIndex();
	LightStruct_t getLightStruct();

	void toggleEnabled();
	bool getEnabled();
	void setEnabled(bool enabled);


	virtual void notify(const Event* event) override;
};
