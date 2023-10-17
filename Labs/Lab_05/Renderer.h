#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "DrawableObject.h"
#include "Camera.h"
#include "Light.h"



class Renderer
{
private:
	std::vector<DrawableObject*> objects;
	std::vector<Light*> lights;
	Camera* camera;

public:
	Renderer();
	~Renderer();

	void addObject(DrawableObject* shape);

	void renderNextFrame(GLFWwindow* window);

	Camera* getCamera();
};
