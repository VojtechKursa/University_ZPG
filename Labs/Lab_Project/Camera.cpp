#include "Camera.h"

#include <stdio.h>

#include "Application.h"
#include "Helper.h"
#include "Lights/LightSpot.h"

#include "Events/CursorEventData.h"
#include "Events/MouseButtonEventData.h"
#include "Events/KeyEventData.h"
#include "Events/CameraEventData.h"
#include "Events/ViewPortChangedEventData.h"
#include "Events/FrameEventData.h"



void Camera::calculateTarget()
{
	calculateTarget(this->alpha, this->phi);
}

void Camera::calculateTarget(float alpha, float phi)
{
	this->target = Helper::convertRotation(alpha, phi);
}



void Camera::calculateViewMatrix()
{
	this->calculateTarget();

	this->viewMatrix = glm::lookAt(eyePosition, eyePosition + target, up);

	const CameraEventData eventData(this->viewMatrix, this->getPosition());
	const Event event(EVENT_CAMERA, (EventData*)&eventData);
	this->notifyAll(&event);
}

void Camera::calculateProjectionMatrix()
{
	this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->viewRatio, this->displayRangeMin, this->displayRangeMax);

	const MatrixEventData data(this->projectionMatrix);
	const Event event(EVENT_PROJECTION_MATRIX, (EventData*)&data);
	this->notifyAll(&event);
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

		if(res.x != 0 || res.z != 0)
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
	this->displayRangeMax = 300.f;

	this->firstCursorEvent = true;
	this->cameraRotationEnabled = false;
	this->lastCursorPoint[0] = this->lastCursorPoint[1] = -1;

	this->mouseSensitivity[0] = this->mouseSensitivity[1] = 1.f;
	this->movementSpeed = 1.f;

	this->motionVector = glm::vec3(0.f);

	this->flying = true;

	this->flashlight = nullptr;

	this->viewPortSize = glm::vec2(0);

	this->calculateViewMatrix();
	this->calculateProjectionMatrix();

	Application::getInstance()->registerObserver(this);
}

Camera::~Camera()
{
	Application::getInstance()->unregisterObserver(this);
}



glm::mat4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}



glm::vec3 Camera::getPosition()
{
	return this->eyePosition;
}

bool Camera::setPosition(glm::vec3 position)
{
	this->eyePosition = position;

	this->calculateViewMatrix();

	this->updateFlashlightPosition();

	return true;
}

Rotation Camera::getRotation()
{
	return Rotation(this->phi, this->alpha, 0);
}

bool Camera::setRotation(Rotation rotation)
{
	this->phi = rotation.yaw;
	this->alpha = rotation.pitch;

	this->calculateViewMatrix();

	this->updateFlashlightRotation();

	return true;
}

LightSpot *Camera::getFlashlight()
{
	return this->flashlight;
}

void Camera::updateFlashlightRotation()
{
	if(this->flashlight != nullptr)
	{
		this->flashlight->setRotation(this->target);
		//this->flashlight->setPosition(this->eyePosition + this->target);	// uncomment for offset (otherwise light rotates on the spot it was left in after last move (also nice))
	}
}

void Camera::updateFlashlightPosition()
{
	if(this->flashlight != nullptr)
	{
		this->flashlight->setPosition(this->eyePosition);
		//this->flashlight->setPosition(this->eyePosition + this->target);	// uncomment for offset
	}
}

bool Camera::addFlashlight(float foi, glm::vec3 lightColor)
{
	if(flashlight != nullptr)
		return false;
	
	if(foi < 0)
		foi = this->fov;

	this->flashlight = new LightSpot(this->eyePosition, this->target, foi, lightColor, false, nullptr, nullptr, nullptr);
	this->flashlight->setAttCoeficients(1);
	
	Application::getInstance()->getRenderer()->addLight(this->flashlight);

	return true;
}



glm::vec2 Camera::getViewPortSize()
{
	return this->viewPortSize;
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



void Camera::notify(const Event *event)
{
	switch(event->eventType)
	{
		case EVENT_MOUSE_BUTTON:
		{
			const MouseButtonEventData* data = static_cast<const MouseButtonEventData*>(event->data);
			this->mouseButtonHandler(data->button, data->action, data->mode);
			break;
		}
		case EVENT_CURSOR:
		{
			const CursorEventData* data = static_cast<const CursorEventData*>(event->data);
			this->cursorMovedHandler(data->x, data->y);
			break;
		}
		case EVENT_KEY:
		{
			const KeyEventData* data = static_cast<const KeyEventData*>(event->data);
			this->keyHandler(data->key, data->scanCode, data->action, data->mods);
			break;
		}
		case EVENT_FRAME:
		{
			const FrameEventData* data = static_cast<const FrameEventData*>(event->data);
			this->frameHandler(data->timeSinceLastFrameSec);
			break;
		}
		case EVENT_VIEWPORT:
		{
			const ViewPortChangedEventData* data = static_cast<const ViewPortChangedEventData*>(event->data);
			this->viewPortChangedHandler(data->newWidth, data->newHeight);
			break;
		}
	}
}

void Camera::cursorMovedHandler(double x, double y)
{
	if(this->cameraRotationEnabled)
	{
		if(!firstCursorEvent)
		{
			this->addPhi((float)(x - this->lastCursorPoint[0]) * this->mouseSensitivity[0]);
			this->addAlpha((float)(y - this->lastCursorPoint[1]) * this->mouseSensitivity[1]);

			this->calculateViewMatrix();

			this->updateFlashlightRotation();
		}

		this->lastCursorPoint[0] = (int)x;
		this->lastCursorPoint[1] = (int)y;
		this->firstCursorEvent = false;

		//printf("New target: %.2f %.2f %.2f\n", this->target.x, this->target.y, this->target.z);
	}
}

void Camera::keyHandler(int key, int scancode, int action, int mods)
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
			if(this->getFlying())
			{
				if(action == GLFW_PRESS)
					this->motionVector += glm::vec3(0,1,0);
				else if(action == GLFW_RELEASE)
					this->motionVector -= glm::vec3(0,1,0);
			}
			break;
		case GLFW_KEY_Y:
		case GLFW_KEY_Z:
			if(this->getFlying())
			{
				if(action == GLFW_PRESS)
					this->motionVector += glm::vec3(0,-1,0);
				else if(action == GLFW_RELEASE)
					this->motionVector -= glm::vec3(0,-1,0);
			}
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
		case GLFW_KEY_L:
			if (action == GLFW_PRESS)
				if(this->flashlight != nullptr)
					this->flashlight->toggleEnabled();
			break;
		/*
		case GLFW_KEY_KP_ADD:
			if (action == GLFW_PRESS)
				if(this->flashlight != nullptr)
				{
					this->flashlight->setFoi(this->flashlight->getFoi() + 1);
					printf("New FOI: %f\n", this->flashlight->getFoi());
				}
			break;
		case GLFW_KEY_KP_SUBTRACT:
			if (action == GLFW_PRESS)
				if(this->flashlight != nullptr)
				{
					this->flashlight->setFoi(this->flashlight->getFoi() - 1);
					printf("New FOI: %f\n", this->flashlight->getFoi());
				}
			break;
		*/
	}
}

void Camera::mouseButtonHandler(int button, int action, int mode)
{
	if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(action == GLFW_PRESS)
		{
			this->cameraRotationEnabled = true;
			
			this->lastCursorPoint[0] = this->lastCursorPoint[1] = 0;
			this->firstCursorEvent = true;
		}
		else if(action == GLFW_RELEASE)
		{
			this->cameraRotationEnabled = false;
		}
	}
}

void Camera::viewPortChangedHandler(int width, int height)
{
	this->viewRatio = width / (float)height;

	this->viewPortSize = glm::vec2(width, height);

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
