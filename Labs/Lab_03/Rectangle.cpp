#include "Rectangle.h"



Rectangle::Rectangle(VAO* vao, ShaderProgram* shaderProgram)
	: Shape(vao, shaderProgram)
{
}

void Rectangle::draw()
{
	Shape::draw();

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); //mode,first,count

	//glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
	//glDrawArrays(GL_TRIANGLES, 1, 3); //mode,first,count
}
