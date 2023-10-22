#pragma once

#include <vector>

#include "Transform.h"



class TransformComposite : public Transform
{
private:
    std::vector<Transform*> subtransforms;

    int findSubtransform(Transform* subtransform);

public:
    TransformComposite();
    TransformComposite(Transform* subtransform);
    TransformComposite(std::vector<Transform*>& subtransforms);
    virtual ~TransformComposite() override;

    virtual glm::mat4 getMatrix() override;

    void addTransform(Transform* transform);
    void removeTransform(Transform* transform);
};

