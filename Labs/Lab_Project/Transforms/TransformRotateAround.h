#pragma once

#include "TransformComposite.h"
#include "TransformRotateSimple.h"
#include "TransformTranslate.h"



class TransformRotateAround : public TransformComposite
{
protected:
    TransformTranslate* there;
    TransformTranslate* back;
    TransformRotateSimple* rotate;

public:
    TransformRotateAround();
    TransformRotateAround(TransformRotateSimple* rotate, glm::vec3 pivotPoint);
    TransformRotateAround(glm::vec3 pivotAxis, float rotationAngle, glm::vec3 pivotPoint);

    glm::vec3 getPivotAxis();
    float getRotationAngle();
    glm::vec3 getPivotPoint();

    bool setPivotAxis(glm::vec3 pivotAxis);
    bool setRotationAngle(float rotationAngle);
    bool setPivotPoint(glm::vec3 pivotPoint);
};

