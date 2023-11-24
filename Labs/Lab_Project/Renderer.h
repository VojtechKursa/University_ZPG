#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "DrawableObject.h"
#include "Camera.h"
#include "Lights/Light.h"
#include "Subject.h"
#include "SkyBox.h"

#include "Interfaces/IObserver.h"
#include "Events/KeyEventData.h"



class Renderer : public Subject, public IObserver
{
private:
	std::vector<DrawableObject*> objects;
	std::vector<Light*> lights;
	Camera* camera;
	SkyBox* skybox = nullptr;

	bool clearZBufferAfterSkybox = true;

	void keyHandler(const KeyEventData* eventData);

public:
	Renderer();
	~Renderer();

	void addObject(DrawableObject* shape);
	void addLight(Light* light);
	void setSkyBox(SkyBox* skybox);

	DrawableObject* removeObject(DrawableObject* object);

	std::vector<Light*> getLights();
	int getLightIndex(Light* light);

	void renderNextFrame(GLFWwindow* window);

	Camera* getCamera();

	virtual void notify(const Event* event) override;
};
