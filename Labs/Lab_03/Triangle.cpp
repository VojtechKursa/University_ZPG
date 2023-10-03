#include "Triangle.h"



Triangle::Triangle(VAO* vao, ShaderProgram* shaderProgram)
	: DrawableObject(vao, shaderProgram)
{ }



void Triangle::draw()
{
	DrawableObject::draw();

	glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
}
