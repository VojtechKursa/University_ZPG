#pragma once

#include "Transform.h"
#include "../Interfaces/ITransformContinuousable.h"



class TransformRotateSimple : public Transform, public ITransformContinuousable
{
public:
    glm::vec3 pivotAxis;
    float rotationAngle;

    TransformRotateSimple();
    
    //* \param pivotAxis The axis of rotation
    //* \param rotationAngle The angle of rotation (in radians)
    TransformRotateSimple(glm::vec3 pivotAxis, float rotationAngle);

    //* \param pivotAxisX The X part of the vector defining the axis of rotation
    //* \param pivotAxisY The Y part of the vector defining the axis of rotation
    //* \param pivotAxisZ The Z part of the vector defining the axis of rotation
    //* \param rotationAngle The angle of rotation (in radians)
    TransformRotateSimple(float pivotAxisX, float pivotAxisY, float pivotAxisZ, float rotationAngle);

    virtual glm::mat4 getMatrix() override;
    virtual void increaseTransformParameter(glm::vec3 increase) override;
};

