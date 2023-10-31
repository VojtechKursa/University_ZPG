#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "Subject.h"
#include "DrawableObject.h"



class Light : public DrawableObject, public Subject, public IObserver
{
private:
	glm::vec3 motionVector;

	glm::vec3 position;
	glm::vec3 lightColor;

	void frameHandler(double timeSinceLastFrameSec);
	void keyHandler(int key, int scancode, int action, int mods);

public:
	Light(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 lightColor = glm::vec3(1, 1, 1), Transform* transformation = nullptr, ShaderProgram* shaderProgram = nullptr, Model* model = nullptr, bool movable = false);

	glm::vec3 getPosition();
	glm::vec3 getLightColor();
	bool hasModel();

	bool setPosition(glm::vec3 position);
	bool setLightColor(glm::vec3 lightColor);

	virtual void notify(const Event* event) override;
};
