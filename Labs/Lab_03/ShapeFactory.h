#pragma once

#include "Triangle.h"
#include "Rectangle.h"



class ShapeFactory
{
public:
	static Triangle* createDefaultTriangle();
	static Triangle* createColoredTriangle();

	static Rectangle* createDefaultSquare();
};
