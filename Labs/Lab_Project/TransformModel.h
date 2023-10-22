#pragma once

#include "TransformComposite.h"
#include "TransformRotate.h"
#include "TransformTranslate.h"
#include "TransformScale.h"



class TransformModel : public TransformComposite
{
private:
    TransformRotate* rotate;
    TransformScale* scale;
    TransformTranslate* translate;

public:
    TransformModel();
    TransformModel(glm::vec3 translationVector, Rotation rotation, glm::vec3 scalingVector);
    TransformModel(TransformTranslate* translate, TransformRotate* rotate, TransformScale* scale);

    virtual glm::mat4 getMatrix() override;

    glm::vec3 getPosition();
    Rotation getRotation();
    glm::vec3 getScale();

    void setPosition(glm::vec3 position);
    void setRotation(Rotation rotation);
    void setScale(glm::vec3 scale);
};

