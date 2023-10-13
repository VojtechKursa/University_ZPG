// These 2 things need to be done first to correctly include header that defines M_PI on Windows
#define _USE_MATH_DEFINES
#include <cmath>

#include "DrawableObjectFactory.h"

#include "VertexShader.h"
#include "FragmentShader.h"

#include "TransformModel.h"
#include "TransformRotateContinuous.h"

#include "sphere.h"
#include "suzi_smooth.h"
#include "suzi_flat.h"



DrawableObject *DrawableObjectFactory::createRotatingSquare()
{
	const float data[] ={
   		-.5f, -.5f,  1.5f,  1, 	1, 1, 0, 1,
   		-.5f,  .5f,  1.5f,  1, 	1, 0, 0, 1,
		 .5f, -.5f,  1.5f,  1, 	0, 1, 0, 1,
   		-.5f,  .5f,  1.5f,  1, 	1, 0, 0, 1,
		 .5f, -.5f,  1.5f,  1, 	0, 1, 0, 1,
   		 .5f,  .5f,  1.5f,  1, 	0, 0, 1, 1,
	};

	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec4 vp;"
		"layout(location=1) in vec4 col;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec4 color;"
		"void main () {"
		"	 gl_Position = projectionMatrix * viewMatrix * modelMatrix * vp;"
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

DrawableObject *DrawableObjectFactory::createDefaultSphere()
{
    const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec3 pos;"
		"layout(location=1) in vec3 norm;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec4 color;"
		"void main () {"
		"	 gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);"
		"	 color = vec4(norm, 1.0);"
		"}";

	const char* fragmentShader =
		"#version 330\n"
		"in vec4 color;"
		"out vec4 frag_colour;"
		"void main () {"
		"	 frag_colour = color;"
		"}";

	VBO* vbo = new VBO();
	vbo->buffer(sphere, sizeof(sphere));

	VAO* vao = new VAO();
	vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(sphere[0]) * 6, nullptr);
	vao->enableVertexAttributes(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(sphere[0]) * 6, sizeof(sphere[0]) * 3);

	Model* model = new Model(vao, 2880);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	TransformModel* transform = new TransformModel();
	transform->setPosition(glm::vec3(0, 0, 10));
	transform->setScale(glm::vec3(0.5));

	return new DrawableObject(model, program, transform);
}

DrawableObject* DrawableObjectFactory::createDefaultSmoothSuzi()
{
	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec3 pos;"
		"layout(location=1) in vec3 norm;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec4 color;"
		"void main () {"
		"	 gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);"
		"	 color = vec4(norm, 1.0);"
		"}";

	const char* fragmentShader =
		"#version 330\n"
		"in vec4 color;"
		"out vec4 frag_colour;"
		"void main () {"
		"	 frag_colour = color;"
		"}";

	VBO* vbo = new VBO();
	vbo->buffer(suziSmooth, sizeof(suziSmooth));

	VAO* vao = new VAO();
	vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(suziSmooth[0]) * 6, nullptr);
	vao->enableVertexAttributes(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(suziSmooth[0]) * 6, sizeof(suziSmooth[0]) * 3);

	Model* model = new Model(vao, 2904);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	TransformModel* transform = new TransformModel();
	transform->setPosition(glm::vec3(2, 0, 8));
	transform->setRotation(Rotation(180, 0, 0));
	transform->setScale(glm::vec3(0.8f));

	return new DrawableObject(model, program, transform);
}

DrawableObject *DrawableObjectFactory::createDefaultFlatSuzi()
{
	const char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec3 pos;"
		"layout(location=1) in vec3 norm;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec4 color;"
		"void main () {"
		"	 gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);"
		"	 color = vec4(norm, 1.0);"
		"}";

	const char* fragmentShader =
		"#version 330\n"
		"in vec4 color;"
		"out vec4 frag_colour;"
		"void main () {"
		"	 frag_colour = color;"
		"}";

	VBO* vbo = new VBO();
	vbo->buffer(suziFlat, sizeof(suziFlat));

	VAO* vao = new VAO();
	vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(suziFlat[0]) * 6, nullptr);
	vao->enableVertexAttributes(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(suziFlat[0]) * 6, sizeof(suziFlat[0]) * 3);

	Model* model = new Model(vao, 2904);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(new VertexShader(vertexShader));
	program->addShader(new FragmentShader(fragmentShader));
	program->link();

	TransformModel* transform = new TransformModel();
	transform->setPosition(glm::vec3(5, 0, 8));
	transform->setRotation(Rotation(180, 0, 0));
	transform->setScale(glm::vec3(0.8f));

	return new DrawableObject(model, program, transform);
}
