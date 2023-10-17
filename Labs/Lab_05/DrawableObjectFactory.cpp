// These 2 things need to be done first to correctly include header that defines M_PI on Windows
#define _USE_MATH_DEFINES
#include <cmath>

#include "DrawableObjectFactory.h"

#include "VertexShader.h"
#include "FragmentShader.h"

#include "TransformModel.h"
#include "TransformRotateContinuous.h"

#include "ModelFactory.h"

#include "ModelManager.h"
#include "ShaderManager.h"



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
	Model* model = ModelManager::getInstance()->get("sphere");

	ShaderProgram* program = new ShaderProgram();
	program->addShader(ShaderManager::getInstance()->get("vert_default_colorPass3"));
	program->addShader(ShaderManager::getInstance()->get("frag_colorFromIn3_grey"));
	program->link();

	TransformComposite* transform = new TransformComposite();
	TransformRotateContinuous* transformRotate = new TransformRotateContinuous(Rotation(10, 0, 0), 'R');
	TransformModel* transformModel = new TransformModel();
	transformModel->setPosition(glm::vec3(0, 0, 10));
	transformModel->setScale(glm::vec3(0.5));
	transform->addTransform(transformRotate);
	transform->addTransform(transformModel);

	return new DrawableObject(model, program, transform);
}

DrawableObject* DrawableObjectFactory::createDefaultSmoothSuzi()
{
	Model* model = ModelManager::getInstance()->get("suzi_smooth");

	ShaderProgram* program = new ShaderProgram();
	program->addShader(ShaderManager::getInstance()->get("vert_default_colorPass4"));
	program->addShader(ShaderManager::getInstance()->get("frag_colorFromIn4"));
	program->link();

	TransformModel* transform = new TransformModel();
	transform->setPosition(glm::vec3(2, 0, 8));
	transform->setRotation(Rotation(180, 0, 0));
	transform->setScale(glm::vec3(0.8f));

	return new DrawableObject(model, program, transform);
}

DrawableObject *DrawableObjectFactory::createDefaultFlatSuzi()
{
	Model* model = ModelManager::getInstance()->get("suzi_flat");

	ShaderProgram* program = new ShaderProgram();
	program->addShader(ShaderManager::getInstance()->get("vert_default_colorPass4"));
	program->addShader(ShaderManager::getInstance()->get("frag_colorFromIn4"));
	program->link();

	TransformModel* transform = new TransformModel();
	transform->setPosition(glm::vec3(5, 0, 8));
	transform->setRotation(Rotation(180, 0, 0));
	transform->setScale(glm::vec3(0.8f));

	return new DrawableObject(model, program, transform);
}

DrawableObject *DrawableObjectFactory::createObject(glm::vec3 position, Rotation rotation, glm::vec3 scale, std::string modelName, std::string vertexShaderName, std::string fragmentShaderName)
{
    Model* model = ModelManager::getInstance()->get(modelName);

	ShaderProgram* program = new ShaderProgram();
	program->addShader(ShaderManager::getInstance()->get(vertexShaderName));
	program->addShader(ShaderManager::getInstance()->get(fragmentShaderName));
	program->link();

	TransformModel* transform = new TransformModel();
	transform->setPosition(position);
	transform->setRotation(rotation);
	transform->setScale(scale);

	return new DrawableObject(model, program, transform);
}

DrawableObject **DrawableObjectFactory::create4SpheresWithLight()
{
	DrawableObject** arr = new DrawableObject*[4];

	const int pos[8] = {
		0,	1,
		1,	0,
		0,	-1,
		-1,	0
	};

	for(int i = 0; i < 8; i+=2)
	{
		arr[i/2] = createObject(glm::vec3(pos[i], 0, pos[i+1]), Rotation(), glm::vec3(0.6f), "sphere", "vert_light", "frag_light_phong");
	}

	return arr;
}
