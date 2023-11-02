#pragma once

#include <string>

#include "DrawableObject.h"
#include "ObjectProperties.h"



class DrawableObjectFactory
{
public:
	static DrawableObject* createRotatingSquare();

	static DrawableObject* createDefaultSphere(std::string vertexShaderName = "vert_default_colorPass3", std::string fragmentShaderName = "frag_colorFromIn3", glm::vec3 position = glm::vec3(0, 0, 10), glm::vec3 scale = glm::vec3(0.5f), Rotation rotateSpeed = Rotation(0, 0, 10));

	static DrawableObject* createDefaultSmoothSuzi(std::string vertexShaderName = "vert_default_colorPass3", std::string fragmentShaderName = "frag_colorFromIn3", glm::vec3 position = glm::vec3(2, 0, 8), Rotation rotation = Rotation(180, 0, 0), glm::vec3 scale = glm::vec3(0.8f));
	static DrawableObject* createDefaultFlatSuzi(std::string vertexShaderName = "vert_default_colorPass3", std::string fragmentShaderName = "frag_colorFromIn3", glm::vec3 position = glm::vec3(5, 0, 8), Rotation rotation = Rotation(180, 0, 0), glm::vec3 scale = glm::vec3(0.8f));
	
	static DrawableObject* createObject(ObjectProperties properties);

	static Light* createLight(glm::vec3 position = glm::vec3(0,0,0), bool movable = true, glm::vec3 color = glm::vec3(1.f), std::string modelName = "sphere", glm::vec3 scale = glm::vec3(0.2f), std::string vertexShaderName = "vert_default_colorPass3", std::string fragmentShaderName = "frag_colorConst");
};
