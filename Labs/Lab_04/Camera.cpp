#include "Camera.h"

#include "Application.h"



void Camera::calculateTarget()
{
	calculateTarget(this->alpha, this->phi);
}

void Camera::calculateTarget(float alpha, float phi)
{
	this->target.x = sin(alpha) * cos(phi);
	this->target.z = sin(alpha) * sin(phi);
	this->target.y = cos(alpha);
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



Camera::Camera()
	: Camera(glm::vec3(0), 0, 0)
{ }

Camera::Camera(glm::vec3 position)
	: Camera(position, 0, 0)
{ }

Camera::Camera(glm::vec3 position, float alpha, float phi)
{
	this->eyePosition = position;
	this->up = glm::vec3(0, 1, 0);

	this->alpha = alpha;
	this->phi = alpha;

	this->calculateTarget();

	this->fov = 45;
	this->viewRatio = 4 / (float)3;

	this->displayRangeMin = 0.1f;
	this->displayRangeMax = 100;

	Application::getInstance()->registerCursorObserver(this);
	Application::getInstance()->registerKeyObserver(this);
}



bool Camera::setPhi(float phi)
{
	if (phi > -90.f && phi < 90.f)
	{
		this->phi = phi;
		return true;
	}
	else
		return false;
}

bool Camera::setAlpha(float alpha)
{
	this->alpha = alpha;
	return true;
}

bool Camera::setFov(float fov)
{
	if (this->fov >= 0 && this->fov <= 360)
	{
		this->fov = fov;
		return true;
	}
	else
		return false;
}

bool Camera::setViewRatio(float viewRatio)
{
	this->viewRatio = viewRatio;
	return true;
}

bool Camera::setDisplayRange(float min, float max)
{
	if (min >= 0 && max >= 0 && min <= max)
	{
		this->displayRangeMin = min;
		this->displayRangeMax = max;

		return true;
	}
	else
		return false;
}



float Camera::getPhi()
{
	return this->phi;
}

float Camera::getAlpha()
{
	return this->alpha;
}



void Camera::registerViewMatrixChangedObserver(IViewMatrixChangedObserver* observer)
{
	this->viewMatrixChangedObservers.push_back(observer);
}

void Camera::registerProjectionMatrixChangedObserver(IProjectionMatrixChangedObserver* observer)
{
	this->projectionMatrixChangedObservers.push_back(observer);
}



glm::mat4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}



void Camera::cursor_callback(GLFWwindow* window, double x, double y)
{

}

void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}
