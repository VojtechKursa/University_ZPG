#include "Renderer.h"

#include "Application.h"

#include "Events/LightCountEventData.h"



Renderer::Renderer()
{
	this->camera = new Camera();
	
	Application::getInstance()->registerObserver(this);
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

	Application::getInstance()->unregisterObserver(this);
}



void Renderer::addObject(DrawableObject* object)
{
	if(object != nullptr)
		this->objects.push_back(object);
}

void Renderer::addLight(Light *light)
{
	if(light != nullptr)
	{
		this->lights.push_back(light);

		LightCountEventData data(light, true, static_cast<int>(this->lights.size() - 1), light->getLightStruct());
		const Event event(EVENT_LIGHT_COUNT, &data);
		this->notifyAll(&event);
	}
}

void Renderer::setSkyBox(SkyBox* skybox)
{
	this->skybox = skybox;
}



DrawableObject* Renderer::removeObject(DrawableObject* object)
{
	int pos = -1;

	for(size_t i = 0; i < this->objects.size(); i++)
	{
		if(this->objects[i] == object)
		{
			pos = static_cast<int>(i);
			break;
		}
	}

	if(pos != -1)
	{
		DrawableObject* selectedObject = this->objects[pos];

		this->objects.erase(this->objects.begin() + pos);

		return selectedObject;
	}
	else
		return nullptr;
}



std::vector<Light *> Renderer::getLights()
{
	return lights;
}

int Renderer::getLightIndex(Light *light)
{
	for(int i = 0; i < this->lights.size(); i++)
	{
		if(this->lights[i] == light)
			return i;
	}

	return -1;
}



void Renderer::renderNextFrame(GLFWwindow* window)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if(this->skybox != nullptr)
	{
		this->skybox->draw();

		if(this->clearZBufferAfterSkybox)
			glClear(GL_DEPTH_BUFFER_BIT);
	}

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



void Renderer::notify(const Event* event)
{
	switch (event->eventType)
	{
		case EVENT_KEY:
			this->keyHandler(static_cast<const KeyEventData*>(event->data));
			break;
	}
}



void Renderer::keyHandler(const KeyEventData* eventData)
{
	if (eventData->key == GLFW_KEY_B && eventData->mods == (GLFW_MOD_ALT | GLFW_MOD_CONTROL) && eventData->action == GLFW_PRESS)
		this->clearZBufferAfterSkybox = !this->clearZBufferAfterSkybox;
}