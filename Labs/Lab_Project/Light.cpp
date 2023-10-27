#include "Light.h"

#include "ObservedSubjectHelper.h"
#include "Transforms/TransformModel.h"
#include "Application.h"



void Light::notifyObservers()
{
    for (auto observer : this->observers)
    {
        observer->lightChangedHandler(this);
    }
}



Light::Light(glm::vec3 position, glm::vec3 lightColor, Transform* transformation, ShaderProgram* shaderProgram, Model* model, bool movable)
    : DrawableObject(model, shaderProgram, transformation)
{
    this->position = position;
    this->lightColor = lightColor;

    this->motionVector = glm::vec3(0.f);

    if(movable)
    {
        Application* application = Application::getInstance();

        application->registerKeyObserver(this);
        application->registerFrameObserver(this);
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

    this->notifyObservers();

    return true;
}

bool Light::setLightColor(glm::vec3 lightColor)
{
    this->lightColor = glm::normalize(lightColor);

    this->notifyObservers();

    return true;
}



bool Light::registerLightObserver(ILightObserver* observer)
{
    bool result = ObservedSubjectHelper::registerObserver(this->observers, observer);

    if(result)
        this->notifyObservers();

    return result;
}

bool Light::unregisterLightObserver(ILightObserver* observer)
{
    return ObservedSubjectHelper::unregisterObserver(this->observers, observer);
}



void Light::frameHandler(double timeSinceLastFrameSec)
{
    if(this->motionVector != glm::vec3(0.f))
    {
        this->setPosition(this->position + glm::normalize(this->motionVector) * (float)timeSinceLastFrameSec);
    }
}

void Light::keyHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
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
