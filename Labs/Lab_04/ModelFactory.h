#pragma once

#include <string>

#include "Model.h"



class ModelFactory
{
public:
    // Creates a new model from a data array containing data in format: 3 position coordinates, 3 normal coordinates
    static Model* createFrom3Pos3Norm(const float* data, unsigned long length);

    // Same as createFrom3Pos3Norm(float* data, int length), but saves the model into a model manager under name
    static Model* createFrom3Pos3Norm(std::string name, const float* data, unsigned long length);
};