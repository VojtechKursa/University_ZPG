#include "TransformRotateAround.h"



TransformRotateAround::TransformRotateAround()
    : TransformRotateAround(new TransformRotateSimple(), glm::vec3(0,0,0))
{ }

TransformRotateAround::TransformRotateAround(TransformRotateSimple *rotate, glm::vec3 pivotPoint)
{
    this->rotate = rotate;
    this->there = new TransformTranslate(-pivotPoint);
    this->back = new TransformTranslate(pivotPoint);

    this->addTransform(this->there);
    this->addTransform(this->rotate);
    this->addTransform(this->back);
}

TransformRotateAround::TransformRotateAround(glm::vec3 pivotAxis, float rotationAngle, glm::vec3 pivotPoint)
    : TransformRotateAround(new TransformRotateSimple(pivotAxis, rotationAngle), pivotPoint)
{ }



glm::vec3 TransformRotateAround::getPivotAxis()
{
    return this->rotate->pivotAxis;
}

float TransformRotateAround::getRotationAngle()
{
    return this->rotate->rotationAngle;
}

glm::vec3 TransformRotateAround::getPivotPoint()
{
    return this->back->translationVector;
}



bool TransformRotateAround::setPivotAxis(glm::vec3 pivotAxis)
{
    this->rotate->pivotAxis = pivotAxis;
    return true;
}

bool TransformRotateAround::setRotationAngle(float rotationAngle)
{
    this->rotate->rotationAngle = rotationAngle;
    return true;
}

bool TransformRotateAround::setPivotPoint(glm::vec3 pivotPoint)
{
    this->there->translationVector = -pivotPoint;
    this->back->translationVector = pivotPoint;
    return true;
}
