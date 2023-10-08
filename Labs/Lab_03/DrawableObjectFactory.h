#pragma once

#include "DrawableObject.h"
#include "MovingObject.h"



class DrawableObjectFactory
{
public:
	static DrawableObject* createDefaultTriangle();

	static DrawableObject* createUpperRightTriangle();
	static DrawableObject* createLowerLeftTriangle();

	static DrawableObject* createDefaultSquare();
	static DrawableObject* createRotatingSquare();
};
