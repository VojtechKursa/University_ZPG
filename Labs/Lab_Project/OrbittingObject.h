#pragma once

#include "DrawableObject.h"
#include "Transforms/TransformRotateAround.h"
#include "Interfaces/IKeyCallbackObserver.h"
#include "Interfaces/IFrameObserver.h"
#include "Rotation.h"


class OrbittingObject : public DrawableObject, public IFrameObserver
{
private:
    void setCurrentTransform(float timeSinceLastFrameSec);

protected:
    bool paused;

    TransformTranslate* translate;
    TransformRotateAround* rotate;

    glm::vec4 startingRelativePosition;

    glm::vec3 pivotPosition;
    OrbittingObject* pivotObject;

public:
    float rotationRate;

    OrbittingObject(Model* model, ShaderProgram* shaderProgram, Transform* transform, glm::vec3 pivotAxis, float rotationRate, glm::vec3 pivotPosition, glm::vec3 startingRelativePosition, Material material = Material());
    OrbittingObject(Model* model, ShaderProgram* shaderProgram, Transform* transform, glm::vec3 pivotAxis, float rotationRate, OrbittingObject* pivotObject, glm::vec3 startingRelativePosition, Material material = Material());
    virtual ~OrbittingObject() override;

    glm::vec4 getPosition();

    virtual void frameHandler(double timeSinceLastFrameSec) override;
};
