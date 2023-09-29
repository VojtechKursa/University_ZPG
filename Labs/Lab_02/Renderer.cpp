#include "Renderer.h"

Renderer::Renderer()
{ }

void Renderer::addShape(Shape* shape)
{
	this->scene.push_back(shape);
}

void Renderer::renderNextFrame(GLFWwindow* window)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto shape : scene)
	{
		shape->draw();
	}

	glfwSwapBuffers(window);
}
