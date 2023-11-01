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
    this->direction = glm::vec3(0.f);

    this->lightType = POINT_LIGHT;

    this->lightColor = lightColor;

    this->motionVector = glm::vec3(0.f);


    if(movable)
    {
        Application::getInstance()->registerObserver(this);
    }
}

Light::Light(glm::vec3 direction, glm::vec3 lightColor, bool movable)
    : Light(glm::vec3(0), lightColor, nullptr, nullptr, nullptr, movable)
{
    this->direction = direction;
    this->lightType = DIRECTIONAL_LIGHT;
}

Light::Light(glm::vec3 position, glm::vec3 direction, glm::vec3 lightColor, Transform *transformation, ShaderProgram *shaderProgram, Model *model, bool movable)
    : Light(position, lightColor, transformation, shaderProgram, model, movable)
{
    this->direction = direction;
    this->lightType = SPOT_LIGHT;
}



int Light::getLightIndex()
{
    return Application::getInstance()->getRenderer()->getLightIndex(this);
}

LightStruct_t Light::getLightStruct()
{
    return LightStruct_t(this->convertLightType(this->lightType), this->position, this->direction, this->lightColor, this->lightStrength, this->constantAttCoeficient, this->linearAttCoeficient, this->quadraticAttCoeficient);
}

int Light::convertLightType(Light::LightType lightType)
{
    switch(lightType)
    {
        case POINT_LIGHT:
            return 0;
        case DIRECTIONAL_LIGHT:
            return 1;
        case SPOT_LIGHT:
            return 2;
        default:
            return -1;
    }
}

Light::LightType Light::convertLightType(int lightType)
{
    switch(lightType)
    {
        case 0:
            return POINT_LIGHT;
        case 1:
            return DIRECTIONAL_LIGHT;
        case 2:
            return SPOT_LIGHT;
        default:
            return LIGHT_TYPE_UNDEFINED;
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

void Light::setAttCoeficients(float lightStrength, float constantAttCoeficient, float linearAttCoeficient, float quadraticAttCoeficient)
{
    this->lightStrength = lightStrength;
    this->constantAttCoeficient = constantAttCoeficient;
    this->linearAttCoeficient = linearAttCoeficient;
    this->quadraticAttCoeficient = quadraticAttCoeficient;

    const LightEventData eventData(this);
    const Event event(EVENT_LIGHT, (EventData*)&eventData);
    this->notifyAll(&event);
}



void Light::notify(const Event *event)
{
    switch(event->eventType)
    {
        case EVENT_FRAME:
        {
            const FrameEventData* data = static_cast<const FrameEventData*>(event->data);
            this->frameHandler(data->timeSinceLastFrameSec);
            break;
        }
        case EVENT_KEY:
        {
            const KeyEventData* data = static_cast<const KeyEventData*>(event->data);
            this->keyHandler(data->key, data->scanCode, data->action, data->mods);
            break;
        }
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
