#pragma once

#include <string>

#include "Model.h"



class ModelLoader
{
private:
	static const std::string modelFolder;

public:
	static Model* loadModel(std::string filename);
};
