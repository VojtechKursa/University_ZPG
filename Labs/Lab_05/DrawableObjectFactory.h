#pragma once

#include <string>

#include "DrawableObject.h"
#include "MovingObject.h"



class DrawableObjectFactory
{
public:
	static DrawableObject* createRotatingSquare();

	static DrawableObject* createDefaultSphere();

	static DrawableObject* createDefaultSmoothSuzi();
	static DrawableObject* createDefaultFlatSuzi();
	
	static DrawableObject* createObject(glm::vec3 position = glm::vec3(0), Rotation rotation = Rotation(), glm::vec3 scale = glm::vec3(1), std::string modelName = "suzi_smooth", std::string vertexShaderName = "vert_default_colorPass4", std::string fragmentShaderName = "frag_colorFromIn4");
};
