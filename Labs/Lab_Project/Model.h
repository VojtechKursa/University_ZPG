#pragma once

#include "VAO.h"

class Model
{
private:
	VAO* vao;

	int firstVertex;
	int vertexCount;
	GLenum drawingMode;

public:
	Model(VAO* vao, int vertexCount, int firstVertex = 0, GLenum drawingMode = GL_TRIANGLES);
	~Model();

	void bind();
	static void unbind();

	void draw();
};

