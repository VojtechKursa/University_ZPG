#include "MovingObject.h"

#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>



MovingObject::MovingObject(Model *model, ShaderProgram *shaderProgram)
    : MovingObject(model, shaderProgram, glm::vec3(0), Rotation(0), glm::vec3(0))
{ }

MovingObject::MovingObject(Model *model, ShaderProgram *shaderProgram, glm::vec3 positionRate, Rotation rotationRate, glm::vec3 scaleRate)
    : DrawableObject(model, shaderProgram)
{
    this->positionRate = positionRate;
    this->rotationRate = rotationRate;
    this->scaleRate = scaleRate;

    this->pauseKey = 0;
    this->pausable = false;

    this->lastTick = (float)glfwGetTime();
    this->paused = false;

    this->transform = new TransformModel();
    this->transformation = this->transform;

    Application::getInstance()->registerKeyObserver(this);
}



void MovingObject::draw()
{
    this->setCurrentTransform();

    DrawableObject::draw();
}



void MovingObject::keyHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(action == 0 && pausable && key == pauseKey)
    {
        if(!this->paused)
            this->setCurrentTransform(); // last transform update before pause

        this->lastTick = (float)glfwGetTime();
        this->paused = !this->paused;
    }
}



void MovingObject::setPauseKey(char pauseKey)
{
    this->pauseKey = pauseKey;
    this->pausable = true;
}

void MovingObject::unsetPauseKey()
{
    this->pauseKey = 0;
    this->pausable = false;
}



void MovingObject::setCurrentTransform()
{
    if(!this->paused)
    {
        float currTime = (float)glfwGetTime();
        float timeDiff = currTime - this->lastTick;

        this->setPosition(this->getPosition() + positionRate * timeDiff);
        this->setRotation(this->getRotation() + rotationRate * timeDiff);
        this->setScale(this->getScale() + scaleRate * timeDiff);

        this->lastTick = currTime;
    }
}



glm::vec3 MovingObject::getPosition()
{
	return this->transform->getPosition();
}

Rotation MovingObject::getRotation()
{
	return this->transform->getRotation();
}

glm::vec3 MovingObject::getScale()
{
	return this->transform->getScale();
}



void MovingObject::setPosition(glm::vec3 newPosition)
{
	this->transform->setPosition(newPosition);
}

void MovingObject::setRotation(Rotation newRotation)
{
	this->transform->setRotation(newRotation);
}

void MovingObject::setScale(glm::vec3 newScale)
{
	this->transform->setScale(newScale);
}
