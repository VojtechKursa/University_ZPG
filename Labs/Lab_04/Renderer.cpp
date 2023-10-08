#include "Renderer.h"



Renderer::Renderer()
{ }

Renderer::~Renderer()
{
	for (auto object : this->scene)
	{
		delete object;
	}
}



void Renderer::addObject(DrawableObject* object)
{
	this->scene.push_back(object);
}

void Renderer::renderNextFrame(GLFWwindow* window)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto object : scene)
	{
		object->draw();
	}

	glfwSwapBuffers(window);
}
