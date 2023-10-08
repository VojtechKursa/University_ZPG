#include "TransformComposite.h"



TransformComposite::TransformComposite()
{ }

TransformComposite::TransformComposite(Transform *subtransform)
{
    this->subtransforms.push_back(subtransform);
}

TransformComposite::TransformComposite(std::vector<Transform *> &subtransforms)
{
    for(auto transform : subtransforms)
    {
        this->subtransforms.push_back(transform);
    }
}

TransformComposite::~TransformComposite()
{
    for(auto& transform : this->subtransforms)
    {
        if(transform != nullptr)
        {
            try
            { delete transform; }
            catch(const std::exception& e)
            { }
            
            transform = nullptr;
        }
    }
}



glm::mat4 TransformComposite::getMatrix()
{
    glm::mat4 matrix = glm::identity<glm::mat4>();

    for(int i = this->subtransforms.size() - 1; i >= 0; i--)
    {
        matrix = matrix * this->subtransforms[i]->getMatrix();
    }

    return matrix;
}



int TransformComposite::findSubtransform(Transform *subtransform)
{
    for(int i = 0; i < this->subtransforms.size(); i++)
    {
        if(this->subtransforms[i] == subtransform)
        {
            return i;
        }
    }

    return -1;
}



void TransformComposite::addTransform(Transform *transform)
{
    this->subtransforms.push_back(transform);
}

void TransformComposite::removeTransform(Transform *transform)
{
    int index = findSubtransform(transform);

    if(index >= 0)
    {
        this->subtransforms.erase(this->subtransforms.begin() + index);
    }
}
