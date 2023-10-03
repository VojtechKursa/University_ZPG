#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Shape.h"



class Renderer
{
private:
	std::vector<DrawableObject*> scene;

public:
	Renderer();
	~Renderer();

	void addShape(DrawableObject* shape);

	void renderNextFrame(GLFWwindow* window);
};
