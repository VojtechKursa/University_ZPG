#include "TransformModel.h"



TransformModel::TransformModel()
    : TransformModel(new TransformTranslate(), new TransformRotate(), new TransformScale())
{ }

TransformModel::TransformModel(glm::vec3 translationVector, Rotation rotation, glm::vec3 scalingVector)
    : TransformModel(new TransformTranslate(translationVector), new TransformRotate(rotation), new TransformScale(scalingVector))
{ }

TransformModel::TransformModel(TransformTranslate *translate, TransformRotate *rotate, TransformScale *scale)
{
    this->translate = translate;
    this->rotate = rotate;
    this->scale = scale;

    addTransform(this->scale);
    addTransform(this->rotate);
    addTransform(this->translate);
}



glm::mat4 TransformModel::getMatrix()
{
    return this->translate->getMatrix() * this->rotate->getMatrix() * this->scale->getMatrix();
}



glm::vec3 TransformModel::getPosition()
{
    return this->translate->translationVector;
}

Rotation TransformModel::getRotation()
{
    return this->rotate->getRotation();
}

glm::vec3 TransformModel::getScale()
{
    return this->scale->scalingVector;
}

void TransformModel::setPosition(glm::vec3 position)
{
    this->translate->translationVector = position;
}

void TransformModel::setRotation(Rotation rotation)
{
    this->rotate->setRotation(rotation);
}

void TransformModel::setScale(glm::vec3 scale)
{
    this->scale->scalingVector = scale;
}
