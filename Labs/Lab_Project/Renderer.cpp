#include "Renderer.h"



Renderer::Renderer()
{
	this->camera = new Camera();
}

Renderer::~Renderer()
{
	for (auto& object : this->objects)
	{
		if(object != nullptr)
		{
			delete object;
			object = nullptr;
		}
	}

	if(this->camera != nullptr)
	{
		delete this->camera;
		this->camera = nullptr;
	}
}



void Renderer::addObject(DrawableObject* object)
{
	if(object != nullptr)
		this->objects.push_back(object);
}

void Renderer::addLight(Light *light)
{
	if(light != nullptr)
		this->lights.push_back(light);
}



std::vector<Light *> Renderer::getLights()
{
    return lights;
}



void Renderer::renderNextFrame(GLFWwindow* window)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto light : lights)
	{
		light->draw();
	}

	for (auto object : objects)
	{
		object->draw();
	}

	glfwSwapBuffers(window);
}

Camera *Renderer::getCamera()
{
	return this->camera;
}
