#pragma once

#include "DrawableObject.h"



class DrawableObjectFactory
{
public:
	static DrawableObject* createDefaultTriangle();
	static DrawableObject* createColoredTriangle();

	static DrawableObject* createDefaultSquare();
};
