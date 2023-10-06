#include "TransformModel.h"



TransformModel::TransformModel()
{
    this->translate = new TransformTranslate();
    this->rotate = new TransformRotate();
    this->scale = new TransformScale();
}

TransformModel::TransformModel(glm::vec3 translationVector, Rotation rotation, glm::vec3 scalingVector)
{
    this->translate = new TransformTranslate(translationVector);
    this->rotate = new TransformRotate(rotation);
    this->scale = new TransformScale(scalingVector);
}

TransformModel::~TransformModel()
{
    if(this->translate != nullptr)
    {
        delete this->translate;
        this->translate = nullptr;
    }

    if(this->rotate != nullptr)
    {
        delete this->rotate;
        this->rotate = nullptr;
    }

    if(this->scale != nullptr)
    {
        delete this->scale;
        this->scale = nullptr;
    }
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
