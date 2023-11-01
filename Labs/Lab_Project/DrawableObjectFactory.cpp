// These 2 things need to be done first to correctly include header that defines M_PI on Windows
#define _USE_MATH_DEFINES
#include <cmath>

#include "DrawableObjectFactory.h"

#include "VertexShader.h"
#include "FragmentShader.h"

#include "Transforms/TransformModel.h"
#include "Transforms/TransformContinuous.h"

#include "ModelFactory.h"

#include "ModelManager.h"
#include "ShaderManager.h"

#include "Application.h"



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

	TransformContinuous* rotation = new TransformContinuous(new TransformRotate(), glm::vec3(0, 0, 30), ' ');
	TransformContinuous* translation = new TransformContinuous(new TransformTranslate(glm::vec3(0,0,0)), glm::vec3(0,0,0.5f), ' ');
	TransformScale* scale = new TransformScale(0.75);

	transform->addTransform(rotation);
	transform->addTransform(scale);
	transform->addTransform(translation);

	return new DrawableObject(model, program, transform);
}

DrawableObject *DrawableObjectFactory::createDefaultSphere(std::string vertexShaderName, std::string fragmentShaderName, glm::vec3 position, glm::vec3 scale, Rotation rotateSpeed)
{
	Model* model = ModelManager::getInstance()->get("sphere");

	ShaderProgram* program = new ShaderProgram();
	program->addShader(ShaderManager::getInstance()->get(vertexShaderName));
	program->addShader(ShaderManager::getInstance()->get(fragmentShaderName));
	program->link();

	TransformComposite* transform = new TransformComposite();
	TransformContinuous* transformRotate = new TransformContinuous(new TransformRotate(), glm::vec3(rotateSpeed.yaw, rotateSpeed.pitch, rotateSpeed.roll), 'R');
	TransformModel* transformModel = new TransformModel();
	transformModel->setPosition(position);
	transformModel->setScale(scale);
	transform->addTransform(transformRotate);
	transform->addTransform(transformModel);

	return new DrawableObject(model, program, transform);
}

DrawableObject* DrawableObjectFactory::createDefaultSmoothSuzi(std::string vertexShaderName, std::string fragmentShaderName, glm::vec3 position, Rotation rotation, glm::vec3 scale)
{
	Model* model = ModelManager::getInstance()->get("suzi_smooth");

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

DrawableObject *DrawableObjectFactory::createDefaultFlatSuzi(std::string vertexShaderName, std::string fragmentShaderName, glm::vec3 position, Rotation rotation, glm::vec3 scale)
{
	Model* model = ModelManager::getInstance()->get("suzi_flat");

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

DrawableObject *DrawableObjectFactory::createObject(ObjectProperties properties)
{
    Model* model = ModelManager::getInstance()->get(properties.modelName);

	ShaderProgram* program = new ShaderProgram(properties.bindToCamera, properties.bindToLights);
	program->addShader(ShaderManager::getInstance()->get(properties.vertexShaderName));
	program->addShader(ShaderManager::getInstance()->get(properties.fragmentShaderName));
	program->link();

	TransformModel* transform = new TransformModel();
	transform->setPosition(properties.position);
	transform->setRotation(properties.rotation);
	transform->setScale(properties.scale);

	return new DrawableObject(model, program, transform, properties.material);
}



Light *DrawableObjectFactory::createLight(glm::vec3 position, bool movable, std::string modelName, glm::vec3 scale, glm::vec3 color, std::string vertexShaderName, std::string fragmentShaderName)
{
	if(modelName != "")
	{
		ShaderProgram* program = new ShaderProgram();
		program->addShader(ShaderManager::getInstance()->get(vertexShaderName));
		program->addShader(ShaderManager::getInstance()->get(fragmentShaderName));
		program->link();

		TransformModel* transform = new TransformModel();
		transform->setScale(scale);
		transform->setPosition(position);

		return new Light(position, color, transform, program, ModelManager::getInstance()->get(modelName), movable);
	}
	else
	{
		return new Light(position, color, nullptr, nullptr, nullptr, movable);
	}
}
