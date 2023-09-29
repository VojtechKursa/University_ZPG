#include "Triangle.h"



Triangle::Triangle(VAO* vao, ShaderProgram* shaderProgram)
	: Shape(vao, shaderProgram)
{ }



void Triangle::draw()
{
	Shape::draw();

	glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
}
