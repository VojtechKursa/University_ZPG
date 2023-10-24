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
		obs->viewMatrixChangedHandler(this->viewMatrix, this->eyePosition);
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



glm::vec3 Camera::getActualMotionVector()
{
	glm::vec3 motionVectorNorm = glm::normalize(this->motionVector);

	glm::vec3 res = glm::vec3(glm::rotate(glm::rotate(glm::identity<glm::mat4>(), glm::radians(phi + 90), glm::vec3(0,1,0)), glm::radians(alpha - 90), glm::vec3(1,0,0)) * glm::vec4(motionVectorNorm, 1.0f));
	res.z = -res.z;

	if (!this->flying)
	{
		res.y = 0;
		res = glm::normalize(res);
	}

	return res;
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
	this->movementSpeed = 1.f;

	this->motionVector = glm::vec3(0.f);

	this->flying = true;

	this->calculateViewMatrix();
	this->calculateProjectionMatrix();

	Application* app = Application::getInstance();
	app->registerCursorObserver(this);
	app->registerKeyObserver(this);
	app->registerButtonObserver(this);
	app->registerViewPortChangedObserver(this);
	app->registerFrameObserver(this);
}

Camera::~Camera()
{
	Application* app = Application::getInstance();
	app->unregisterCursorObserver(this);
	app->unregisterKeyObserver(this);
	app->unregisterButtonObserver(this);
	app->unregisterViewPortChangedObserver(this);
	app->unregisterFrameObserver(this);
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



bool Camera::setPosition(glm::vec3 position)
{
	this->eyePosition = position;

	this->calculateViewMatrix();

	return true;
}

bool Camera::setRotation(Rotation rotation)
{
	this->phi = rotation.yaw;
	this->alpha = rotation.pitch;

	this->calculateViewMatrix();

	return true;
}



bool Camera::setFlying(bool flying)
{
	this->flying = flying;
	return true;
}

bool Camera::getFlying()
{
	return this->flying;
}



void Camera::cursorMovedHandler(GLFWwindow* window, double x, double y)
{
	if(this->mouseButtonHeld)
	{
		if(!firstCursorEvent)
		{
			this->addPhi((float)(x - this->lastCursorPoint[0]) * this->mouseSensitivity[0]);
			this->addAlpha((float)(y - this->lastCursorPoint[1]) * this->mouseSensitivity[1]);
		}

		this->lastCursorPoint[0] = (int)x;
		this->lastCursorPoint[1] = (int)y;
		this->firstCursorEvent = false;

		this->calculateViewMatrix();

		//printf("New target: %.2f %.2f %.2f\n", this->target.x, this->target.y, this->target.z);
	}
}

void Camera::keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
		case GLFW_KEY_W:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(0,0,1);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(0,0,1);
			break;
		case GLFW_KEY_S:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(0,0,-1);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(0,0,-1);
			break;
		case GLFW_KEY_A:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(-1,0,0);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(-1,0,0);
			break;
		case GLFW_KEY_D:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(1,0,0);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(1,0,0);
			break;
		case GLFW_KEY_Q:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(0,1,0);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(0,1,0);
			break;
		case GLFW_KEY_Y:
		case GLFW_KEY_Z:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(0,-1,0);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(0,-1,0);
			break;
		case GLFW_KEY_LEFT_SHIFT:
			if(action == GLFW_PRESS)
				this->movementSpeed *= 4;
			else if (action == GLFW_RELEASE)
				this->movementSpeed /= 4;
			break;
		case GLFW_KEY_V:
			if (action == GLFW_PRESS)
				this->setFlying(!this->getFlying());
			break;
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

void Camera::frameHandler(double timeSinceLastFrameSec)
{
	if(this->motionVector != glm::vec3(0.f))
	{
		glm::vec3 actualMotionVector = this->getActualMotionVector();

		glm::vec3 newEyePos = this->eyePosition + (actualMotionVector * this->movementSpeed * (float)timeSinceLastFrameSec);

		//printf("Motion vector: (%.2f, %.2f, %.2f). Camera target: (%.2f, %.2f, %.2f). Actual motion vector: (%.2f, %.2f, %.2f).\n", this->motionVector.x, this->motionVector.y, this->motionVector.z, this->target.x, this->target.y, this->target.z, actualMotionVector.x, actualMotionVector.y, actualMotionVector.z);

		this->setPosition(newEyePos);
	}
}
