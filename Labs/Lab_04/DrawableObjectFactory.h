#pragma once

#include "DrawableObject.h"
#include "MovingObject.h"



class DrawableObjectFactory
{
public:
	static DrawableObject* createRotatingSquare();

	static DrawableObject* createDefaultSphere();

	static DrawableObject* createDefaultSmoothSuzi();
	static DrawableObject* createDefaultFlatSuzi();
};
