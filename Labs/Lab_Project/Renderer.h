#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "DrawableObject.h"
#include "Camera.h"
#include "Lights/Light.h"
#include "Subject.h"
#include "SkyBox.h"



class Renderer : public Subject
{
private:
	std::vector<DrawableObject*> objects;
	std::vector<Light*> lights;
	Camera* camera;
	SkyBox* skybox = nullptr;

public:
	Renderer();
	~Renderer();

	void addObject(DrawableObject* shape);
	void addLight(Light* light);
	void setSkyBox(SkyBox* skybox);

	std::vector<Light*> getLights();
	int getLightIndex(Light* light);

	void renderNextFrame(GLFWwindow* window);

	Camera* getCamera();
};
