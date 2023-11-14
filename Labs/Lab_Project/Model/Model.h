#pragma once

#include "../VAO.h"

class Model
{
private:
	VAO* vao;

	GLint firstVertex;
	GLsizei vertexCount;
	GLenum drawingMode;

public:
	Model(VAO* vao, GLsizei vertexCount, GLint firstVertex = 0, GLenum drawingMode = GL_TRIANGLES);
	~Model();

	void bind();
	static void unbind();

	void draw();
};

