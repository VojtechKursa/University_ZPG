#pragma once
#include <GL/glew.h>

class Shape
{
private:
	GLuint vboID;

	float* points;
	int pointsLength;
};

