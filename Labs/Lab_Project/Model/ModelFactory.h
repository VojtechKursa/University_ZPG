#pragma once

#include <string>

#include "Model.h"



class ModelFactory
{
public:
    // Creates a new model from a data array containing data in format: 3 position coordinates, 3 normal coordinates
    static Model* createFrom3Pos3Norm(const float* data, unsigned long length);

    // Creates a new model from a data array containing data in format: 3 position coordinates, 3 normal coordinates and 2 texture coordinates
    static Model* createFrom3Pos3Norm2Tex(const float* data, unsigned long length);

    // Creates a new model from a data array containing data in format: 3 position coordinates
    static Model* createFrom3Pos(const float* data, unsigned long length);
};