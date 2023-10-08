// THese 2 things need to be done first to correctly include header that defines M_PI on Windows
#define _USE_MATH_DEFINES
#include <cmath>

#include "DrawableObjectFactory.h"

#include "VertexShader.h"
#include "FragmentShader.h"

#include "TransformModel.h"
#include "TransformRotateContinuous.h"



DrawableObject* DrawableObjectFactory::createDefaultTriangle()
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

	Model* model = new Model(vao, 3);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	return new DrawableObject(model, program);
}

DrawableObject* DrawableObjectFactory::createUpperRightTriangle()
{
	const float points[] = {
		0.0f, 0.0f, -0.5f,
	    0.5f, 0.0f, -0.5f,
	  	0.0f, 0.5f, -0.5f
	};

	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"uniform mat4 modelMatrix;"
		"out vec4 loc;"
		"void main () {"
		"	 gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"	 loc = gl_Position;"
		"}";

	const char* fragmentShader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 loc;"
		"void main () {"
		"	 frag_colour = loc;"
		"}";

	VBO* vbo = new VBO();
	vbo->buffer(points, sizeof(points));

	VAO* vao = new VAO();
	vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	Model* model = new Model(vao, 3);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	TransformComposite* transform = new TransformComposite();
	TransformTranslate* translate = new TransformTranslate(glm::vec3(0.9f, 0.9f, -0.5f));
	TransformRotate* rotate = new TransformRotate(Rotation(0, 0, (float)M_PI));
	
	transform->addTransform(rotate);
	transform->addTransform(translate);

	return new DrawableObject(model, program, transform);
}

DrawableObject *DrawableObjectFactory::createLowerLeftTriangle()
{
    const float points[] = {
		0.0f, 0.0f, 0.0f,
	    0.5f, 0.0f, 0.0f,
	  	0.0f, 0.5f, 0.0f
	};

	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"uniform mat4 modelMatrix;"
		"out vec4 loc;"
		"void main () {"
		"	 gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"	 loc = gl_Position;"
		"}";

	const char* fragmentShader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 loc;"
		"void main () {"
		"	 frag_colour = -1 * loc;"
		"}";

	VBO* vbo = new VBO();
	vbo->buffer(points, sizeof(points));

	VAO* vao = new VAO();
	vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	Model* model = new Model(vao, 3);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	TransformComposite* transform = new TransformComposite();
	TransformTranslate* translate = new TransformTranslate(glm::vec3(-0.9, -0.9, 0.5));
	TransformScale* scale = new TransformScale(0.5);

	transform->addTransform(scale);
	transform->addTransform(translate);

	return new DrawableObject(model, program, transform);
}

DrawableObject* DrawableObjectFactory::createDefaultSquare()
{
	const float data[] ={
   		-.5f, -.5f,  .5f,  1, 	1, 1, 0, 1,
   		-.5f,  .5f,  .5f,  1, 	1, 0, 0, 1,
		 .5f, -.5f,  .5f,  1, 	0, 1, 0, 1,
   		-.5f,  .5f,  .5f,  1, 	1, 0, 0, 1,
		 .5f, -.5f,  .5f,  1, 	0, 1, 0, 1,
   		 .5f,  .5f,  .5f,  1, 	0, 0, 1, 1,
	};

	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec4 vp;"
		"layout(location=1) in vec4 col;"
		"uniform mat4 modelMatrix;"
		"out vec4 color;"
		"void main () {"
		"	 gl_Position = modelMatrix * vp;"
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
	vao->enableVertexAttributes(vbo, 0, 4, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 8, nullptr);
	vao->enableVertexAttributes(vbo, 1, 4, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 8, sizeof(data[0]) * 4);

	Model* model = new Model(vao, 6);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	return new DrawableObject(model, program);
}

DrawableObject *DrawableObjectFactory::createRotatingSquare()
{
	const float data[] ={
   		-.5f, -.5f,  .5f,  1, 	1, 1, 0, 1,
   		-.5f,  .5f,  .5f,  1, 	1, 0, 0, 1,
		 .5f, -.5f,  .5f,  1, 	0, 1, 0, 1,
   		-.5f,  .5f,  .5f,  1, 	1, 0, 0, 1,
		 .5f, -.5f,  .5f,  1, 	0, 1, 0, 1,
   		 .5f,  .5f,  .5f,  1, 	0, 0, 1, 1,
	};

	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec4 vp;"
		"layout(location=1) in vec4 col;"
		"uniform mat4 modelMatrix;"
		"out vec4 color;"
		"void main () {"
		"	 gl_Position = modelMatrix * vp;"
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
	vao->enableVertexAttributes(vbo, 0, 4, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 8, nullptr);
	vao->enableVertexAttributes(vbo, 1, 4, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 8, sizeof(data[0]) * 4);

	Model* model = new Model(vao, 6);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	TransformComposite* transform = new TransformComposite();

	TransformRotateContinuous* rotation = new TransformRotateContinuous(Rotation(0,0,(float)M_PI/(float)8), ' ');
	TransformScale* scale = new TransformScale(0.75);

	transform->addTransform(rotation);
	transform->addTransform(scale);

	return new DrawableObject(model, program, transform);
}
