#include "Light.h"

#include "ObservedSubjectHelper.h"



void Light::notifyObservers()
{
    for (auto observer : this->observers)
    {
        observer->lightChangedHandler(this);
    }
}



Light::Light(glm::vec3 position, glm::vec3 lightColor, Transform* transformation, ShaderProgram* shaderProgram, Model* model)
    : DrawableObject(model, shaderProgram, transformation)
{
    this->position = position;
    this->lightColor = lightColor;
}



glm::vec3 Light::getPosition()
{
    return this->position;
}

glm::vec3 Light::getLightColor()
{
    return this->lightColor;
}



bool Light::setPosition(glm::vec3 position)
{
    this->position = position;

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
    return ObservedSubjectHelper::registerObserver(this->observers, observer);
}

bool Light::unregisterLightObserver(ILightObserver* observer)
{
    return ObservedSubjectHelper::unregisterObserver(this->observers, observer);
}
