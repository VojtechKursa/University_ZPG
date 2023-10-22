#include "Camera.h"

#include <stdio.h>

#include "Application.h"
#include "ObservedSubjectHelper.h"



void Camera::calculateTarget()
{
	calculateTarget(this->alpha, this->phi);
}

void Camera::calculateTarget(float alpha, float phi)
{
	float alphaRad = glm::radians(alpha);
	float phiRad = glm::radians(phi);

	this->target.x = sin(alphaRad) * cos(phiRad);
	this->target.z = sin(alphaRad) * sin(phiRad);
	this->target.y = cos(alphaRad);
}

void Camera::calculateViewMatrix()
{
	this->calculateTarget();

	this->viewMatrix = glm::lookAt(eyePosition, eyePosition + target, up);

	for (auto obs : this->viewMatrixChangedObservers)
	{
		obs->viewMatrixChangedHandler(this->viewMatrix);
	}
}

void Camera::calculateProjectionMatrix()
{
	this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->viewRatio, this->displayRangeMin, this->displayRangeMax);

	for (auto obs : this->projectionMatrixChangedObservers)
	{
		obs->projectionMatrixChangedHandler(this->projectionMatrix);
	}
}



void Camera::addAlpha(float change)
{
	this->alpha += change;

	if(alpha >= 180)
	{
		this->alpha = 179.9f;
	}
	else if(alpha <= 0)
	{
		this->alpha = 0.1f;
	}
}

void Camera::addPhi(float change)
{
	this->phi += change;

	while(phi < 0)
	{
		this->phi += 360;
	}
	while(phi >= 360)
	{
		this->phi -= 360;
	}
}



Camera::Camera()
	: Camera(glm::vec3(0), 90, 90)
{ }

Camera::Camera(glm::vec3 position)
	: Camera(position, 90, 90)
{ }

Camera::Camera(glm::vec3 position, float alpha, float phi)
{
	this->eyePosition = position;
	this->up = glm::vec3(0, 1, 0);

	this->alpha = alpha;
	this->phi = alpha;

	this->fov = 45;
	this->viewRatio = 4 / (float)3;

	this->displayRangeMin = 0.1f;
	this->displayRangeMax = 100.f;

	this->firstCursorEvent = true;
	this->mouseButtonHeld = false;
	this->lastCursorPoint[0] = this->lastCursorPoint[1] = -1;

	this->mouseSensitivity[0] = this->mouseSensitivity[1] = 1.f;
	this->movementSensitivity = 1.f;

	this->calculateViewMatrix();
	this->calculateProjectionMatrix();

	Application* app = Application::getInstance();
	app->registerCursorObserver(this);
	app->registerKeyObserver(this);
	app->registerButtonObserver(this);
	app->registerViewPortChangedObserver(this);
}

Camera::~Camera()
{
	Application* app = Application::getInstance();
	app->unregisterCursorObserver(this);
	app->unregisterKeyObserver(this);
	app->unregisterButtonObserver(this);
	app->unregisterViewPortChangedObserver(this);
}



bool Camera::registerViewMatrixChangedObserver(IViewMatrixChangedObserver* observer)
{
	return ObservedSubjectHelper::registerObserver(this->viewMatrixChangedObservers, observer);
}

bool Camera::registerProjectionMatrixChangedObserver(IProjectionMatrixChangedObserver* observer)
{
	return ObservedSubjectHelper::registerObserver(this->projectionMatrixChangedObservers, observer);
}

bool Camera::unregisterViewMatrixChangedObserver(IViewMatrixChangedObserver *observer)
{
	return ObservedSubjectHelper::unregisterObserver(this->viewMatrixChangedObservers, observer);
}

bool Camera::unregisterProjectionMatrixChangedObserver(IProjectionMatrixChangedObserver *observer)
{
	return ObservedSubjectHelper::unregisterObserver(this->projectionMatrixChangedObservers, observer);
}



glm::mat4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}



void Camera::cursorMovedHandler(GLFWwindow* window, double x, double y)
{
	if(this->mouseButtonHeld)
	{
		if(!firstCursorEvent)
		{
			this->addPhi((x - this->lastCursorPoint[0]) * this->mouseSensitivity[0]);
			this->addAlpha((y - this->lastCursorPoint[1]) * this->mouseSensitivity[1]);
		}

		this->lastCursorPoint[0] = x;
		this->lastCursorPoint[1] = y;
		this->firstCursorEvent = false;

		this->calculateViewMatrix();

		printf("New target: %.2f %.2f %.2f\n", this->target.x, this->target.y, this->target.z);
	}
}

void Camera::keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == 1)
	{
		switch (key)
		{
			case 'W':
				this->eyePosition += this->target * this->movementSensitivity;
				this->calculateViewMatrix();
				break;
			case 'S':
				this->eyePosition -= this->target * this->movementSensitivity;
				this->calculateViewMatrix();
				break;
			case 'A':
				this->eyePosition -= glm::normalize(glm::cross(this->target, this->up)) * this->movementSensitivity;
				this->calculateViewMatrix();
				break;
			case 'D':
				this->eyePosition += glm::normalize(glm::cross(this->target, this->up)) * this->movementSensitivity;
				this->calculateViewMatrix();
				break;
		}
	}
}

void Camera::mouseButtonPressedHandler(GLFWwindow* window, int button, int action, int mode)
{
	if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(action == GLFW_PRESS)
		{
			this->mouseButtonHeld = true;
		}
		else if(action == GLFW_RELEASE)
		{
			this->mouseButtonHeld = false;
		}
	}
}

void Camera::viewPortChangedHandler(int width, int height)
{
	this->viewRatio = width / (float)height;

	this->calculateProjectionMatrix();
}
