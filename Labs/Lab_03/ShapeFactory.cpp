#include "ShapeFactory.h"

#include "VertexShader.h"
#include "FragmentShader.h"



Triangle* ShapeFactory::createDefaultTriangle()
{
	const float points[] = {
	   0.0f, 0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f
	};

	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"	 gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragmentShader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"	 frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

	VBO* vbo = new VBO();
	vbo->buffer(points, sizeof(points));

	VAO* vao = new VAO();
	vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	return new Triangle(vao, program);
}

Triangle* ShapeFactory::createColoredTriangle()
{
	const float points[] = {
		  0.0f, 1.0f, 0.0f,
		  0.5f, 0.5f, 0.0f,
		 -0.5f, 0.5f, 0.0f
	};

	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"uniform mat4 modelMatrix;"
		"out vec3 loc;"
		"void main () {"
		"	 gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"	 loc = vp;"
		"}";

	const char* fragmentShader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec3 loc;"
		"void main () {"
		"	 frag_colour = vec4 (loc + vec3(0.5, 0.0, 0.0), 1.0);"
		"}";

	VBO* vbo = new VBO();
	vbo->buffer(points, sizeof(points));

	VAO* vao = new VAO();
	vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	return new Triangle(vao, program);
}

Rectangle* ShapeFactory::createDefaultSquare()
{
	const float data[] = {
		   -1.f, -.5f, .5f, 1, 1, 1, 0, 1,
		   -1.f, .5f, .5f, 1, 1, 0, 0, 1,
		   0.f, .5f, .5f, 1, 0, 0, 0, 1,
		   0.f, -.5f, .5f, 1, 0, 1, 0, 1,
	};

	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec4 vp;"
		"layout(location=1) in vec4 col;"
		"out vec4 color;"
		"void main () {"
		"	 gl_Position = vp;"
		"	 color = col;"
		"}";

	const char* fragmentShader =
		"#version 330\n"
		"in vec4 color;"
		"out vec4 frag_colour;"
		"void main () {"
		"	 frag_colour = color;"
		"}";

	VBO* vbo = new VBO();
	vbo->buffer(data, sizeof(data));

	VAO* vao = new VAO();
	vao->enableVertexAttributes(vbo, 0, 4, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 8, (size_t)0);
	vao->enableVertexAttributes(vbo, 1, 4, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 8, sizeof(data[0]) * 4);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	return new Rectangle(vao, program);
}
