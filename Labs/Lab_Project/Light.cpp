#include "Light.h"

#include "Transforms/TransformModel.h"
#include "Application.h"

#include "Events/FrameEventData.h"
#include "Events/KeyEventData.h"
#include "Events/LightEventData.h"



Light::Light(glm::vec3 position, glm::vec3 lightColor, Transform* transformation, ShaderProgram* shaderProgram, Model* model, bool movable)
    : DrawableObject(model, shaderProgram, transformation, Material(lightColor))
{
    this->position = position;
    this->lightColor = lightColor;

    this->motionVector = glm::vec3(0.f);

    if(movable)
    {
        Application::getInstance()->registerObserver(this);
    }
}



glm::vec3 Light::getPosition()
{
    return this->position;
}

glm::vec3 Light::getLightColor()
{
    return this->lightColor;
}

bool Light::hasModel()
{
    return this->model != nullptr;
}



bool Light::setPosition(glm::vec3 position)
{
    this->position = position;

    if(this->transformation != nullptr)
    {
        TransformModel* transform = (TransformModel*)this->transformation;

        if(transform != nullptr)
        {
            transform->setPosition(position);
        }
    }

    const LightEventData eventData(this);
    const Event event(EVENT_LIGHT, (EventData*)&eventData);
    this->notifyAll(&event);

    return true;
}

bool Light::setLightColor(glm::vec3 lightColor)
{
    this->lightColor = glm::normalize(lightColor);

    const LightEventData eventData(this);
    const Event event(EVENT_LIGHT, (EventData*)&eventData);
    this->notifyAll(&event);

    return true;
}



void Light::notify(const Event *event)
{
    const FrameEventData* frameData;
    const KeyEventData* keyData;

    switch(event->eventType)
    {
        case EVENT_FRAME:
            frameData = static_cast<const FrameEventData*>(event->data);
            this->frameHandler(frameData->timeSinceLastFrameSec);
            break;
        case EVENT_KEY:
            keyData = static_cast<const KeyEventData*>(event->data);
            this->keyHandler(keyData->key, keyData->scanCode, keyData->action, keyData->mods);
            break;
    }
}

void Light::frameHandler(double timeSinceLastFrameSec)
{
    if(this->motionVector != glm::vec3(0.f))
    {
        this->setPosition(this->position + glm::normalize(this->motionVector) * (float)timeSinceLastFrameSec);
    }
}

void Light::keyHandler(int key, int scancode, int action, int mods)
{
    switch(key)
    {
        case GLFW_KEY_KP_8:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(0,0,1);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(0,0,1);
			break;
		case GLFW_KEY_KP_2:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(0,0,-1);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(0,0,-1);
			break;
		case GLFW_KEY_KP_4:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(1,0,0);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(1,0,0);
			break;
		case GLFW_KEY_KP_6:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(-1,0,0);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(-1,0,0);
			break;
		case GLFW_KEY_KP_9:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(0,1,0);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(0,1,0);
			break;
		case GLFW_KEY_KP_3:
			if(action == GLFW_PRESS)
				this->motionVector += glm::vec3(0,-1,0);
			else if(action == GLFW_RELEASE)
				this->motionVector -= glm::vec3(0,-1,0);
			break;
        case GLFW_KEY_KP_5:
            if(action == GLFW_PRESS)
                this->setPosition(glm::vec3(0));
            break;
        case GLFW_KEY_T:
            if(action == GLFW_PRESS)
                this->setPosition(Application::getInstance()->getRenderer()->getCamera()->getPosition() + glm::vec3(0,1,0));
            break;
    }
}
