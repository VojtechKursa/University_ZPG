#pragma once

#include "DrawableObject.h"
#include "TransformModel.h"
#include "IKeyCallbackListener.h"


class MovingObject : public DrawableObject, public IKeyCallbackListener
{
private:
    void setCurrentTransform();

protected:
    char pauseKey;
    bool pausable;

    float lastTick;
    bool paused;

    TransformModel* transform;

public:
    glm::vec3 positionRate;
    Rotation rotationRate;
    glm::vec3 scaleRate;

	MovingObject(Model* model, ShaderProgram* shaderProgram);
    MovingObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 positionRate, Rotation rotationRate, glm::vec3 scaleRate);

    void setPauseKey(char pauseKey);
    void unsetPauseKey();

    glm::vec3 getPosition();
	Rotation getRotation();
	glm::vec3 getScale();

	void setPosition(glm::vec3 newPosition);
	void setRotation(Rotation newRotation);
	void setScale(glm::vec3 newScale);

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) override;    

	virtual void draw() override;
};

