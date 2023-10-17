#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "ILightObserver.h"
#include "DrawableObject.h"



class Light : public DrawableObject
{
private:
	std::vector<ILightObserver*> observers;

	void notifyObservers();

	glm::vec3 position;
	glm::vec3 lightColor;

public:
	Light(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 lightColor = glm::vec3(1, 1, 1), Transform* transformation = nullptr, ShaderProgram* shaderProgram = nullptr, Model* model = nullptr);

	glm::vec3 getPosition();
	glm::vec3 getLightColor();

	bool setPosition(glm::vec3 position);
	bool setLightColor(glm::vec3 lightColor);

	bool registerLightObserver(ILightObserver* observer);

	bool unregisterLightObserver(ILightObserver* observer);
};
