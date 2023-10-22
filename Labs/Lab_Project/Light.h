#pragma once

#include <glm/ext.hpp>

#include <vector>

#include "Interfaces/ILightObserver.h"
#include "Interfaces/IKeyCallbackObserver.h"
#include "Interfaces/IFrameObserver.h"
#include "DrawableObject.h"



class Light : public DrawableObject, public IKeyCallbackObserver, public IFrameObserver
{
private:
	std::vector<ILightObserver*> observers;
	glm::vec3 motionVector;

	void notifyObservers();

	glm::vec3 position;
	glm::vec3 lightColor;

public:
	Light(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 lightColor = glm::vec3(1, 1, 1), Transform* transformation = nullptr, ShaderProgram* shaderProgram = nullptr, Model* model = nullptr, bool movable = false);

	glm::vec3 getPosition();
	glm::vec3 getLightColor();
	bool hasModel();

	bool setPosition(glm::vec3 position);
	bool setLightColor(glm::vec3 lightColor);

	bool registerLightObserver(ILightObserver* observer);

	bool unregisterLightObserver(ILightObserver* observer);

	virtual void frameHandler(double timeSinceLastFrameSec) override;
	virtual void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};
