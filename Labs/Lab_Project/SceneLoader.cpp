#include "SceneLoader.h"

#include "DrawableObjectFactory.h"
#include "Helper.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "Transforms/TransformContinuous.h"
#include "Transforms/TransformTranslate.h"



const LightModel SceneLoader::lightModels[] = {CONST, LAMBERT, PHONG, BLINN};
const int SceneLoader::lightModelsCount = sizeof(lightModels) / sizeof(LightModel);



std::string SceneLoader::getFragmentShaderName(LightModel lightModel)
{
    switch(lightModel)
    {
        case CONST:
            return "frag_light_const";
        case LAMBERT:
            return "frag_light_lambert";
        case PHONG:
            return "frag_light_phong";
        case BLINN:
            return "frag_light_blinn";
        default:
            return "frag_light_const";
    }
}



void SceneLoader::loadRotatingSquare(Renderer* renderer)
{
    renderer->addObject(DrawableObjectFactory::createRotatingSquare());
}

void SceneLoader::loadContinuousMovementDemo(Renderer* renderer)
{
    Camera* camera = renderer->getCamera();
    camera->setRotation(Rotation(270, 90, 0));


    TransformContinuous* transform = new TransformContinuous(new TransformTranslate(-5, 0, -10), glm::vec3(1,0,0), 'P');
    Model* sphere = ModelManager::getInstance()->get("sphere");
    ShaderManager* shaderManager = ShaderManager::getInstance();

    Shader* frag = shaderManager->get("vert_default_colorPass3");
    Shader* vert = shaderManager->get("frag_colorFromIn3");
    
    ShaderProgram* shader = new ShaderProgram();
    shader->addShader(frag);
    shader->addShader(vert);
    shader->link();

    renderer->addObject(new DrawableObject(sphere, shader, transform));
}

void SceneLoader::loadDefault3DScene(Renderer* renderer)
{
    renderer->addObject(DrawableObjectFactory::createDefaultSphere());
	renderer->addObject(DrawableObjectFactory::createDefaultSmoothSuzi());
	renderer->addObject(DrawableObjectFactory::createDefaultFlatSuzi());

    ObjectProperties properties;
    properties.modelName = "suzi_smooth";
    properties.position = glm::vec3(0,0,-2);

	renderer->addObject(DrawableObjectFactory::createObject(properties));
}

void SceneLoader::loadLightsDemoScene(Renderer* renderer)
{
    renderer->addLight(DrawableObjectFactory::createLight(glm::vec3(0,0,3)));

    ObjectProperties properties;
    properties.scale = glm::vec3(0.7f);
    properties.position = glm::vec3(2, 0, 3);
    properties.vertexShaderName = "vert_light";
    properties.bindToLights = true;

    for(int i = 0; i < lightModelsCount; i++)
    {
        properties.fragmentShaderName = getFragmentShaderName(lightModels[i]);

        for(int j = 0; j < 2; j++)
        {
            switch(j)
            {
                case 0:
                    properties.rotation.yaw = 0;
                    properties.modelName = "sphere";
                    break;
                case 1:
                    properties.rotation.yaw = 90;
                    properties.modelName = "suzi_smooth";
                    break;
            }

            renderer->addObject(DrawableObjectFactory::createObject(properties));

            properties.position.x *= -1;
        }

        properties.position.z += 3;
    }

    Camera* camera = renderer->getCamera();
    camera->setPosition(glm::vec3(0,3,0));
    camera->setRotation(Rotation(90, 120, 0));
}

void SceneLoader::loadSphereWithLight(Renderer* renderer, LightModel lightModel)
{
    renderer->addLight(DrawableObjectFactory::createLight(glm::vec3(0, 0, 8)));

    ObjectProperties properties;
    properties.position = glm::vec3(0,0,4);
    properties.scale = glm::vec3(0.5f);
    properties.modelName = "sphere";
    properties.vertexShaderName = "vert_light";
    properties.fragmentShaderName = getFragmentShaderName(lightModel);
    properties.bindToLights = true;

    renderer->addObject(DrawableObjectFactory::createObject(properties));
}

void SceneLoader::loadSpheresWithLight(Renderer* renderer, LightModel lightModel)
{
    renderer->addLight(DrawableObjectFactory::createLight());

	const int pos[8] = {
		0,	2,
		2,	0,
		0,	-2,
		-2,	0
	};

    ObjectProperties properties;
    properties.modelName = "sphere";
    properties.vertexShaderName = "vert_light";
    properties.fragmentShaderName = getFragmentShaderName(lightModel);
    properties.bindToLights = true;

	for(int i = 0; i < 8; i+=2)
	{
        properties.position = glm::vec3(pos[i], 0, pos[i+1]);

		renderer->addObject(DrawableObjectFactory::createObject(properties));
	}

    Camera* camera = renderer->getCamera();
	camera->setPosition(glm::vec3(0,8,0));
	camera->setRotation(Rotation(90,179.9f,0));
}

void SceneLoader::loadForest(Renderer* renderer)
{
    struct generatorParams
    {
        std::string name;
        int count;
        int maxTilt;
        bool randomizeShaders = false;
        int yOffset = 0;
        float scale = 1;
    };

    const int plainSize = 50;
    const struct generatorParams generatorParameters[] = {
        {"tree", 100, 10, true},
        {"gift", 10, 0},
        {"bushes", 25, 20},
        {"suzi_smooth", 5, 0, true, 1, 0.5f}
    };



    renderer->addLight(DrawableObjectFactory::createLight());

    ObjectProperties plainProperties;
    plainProperties.scale = glm::vec3(plainSize, 1, plainSize);
    plainProperties.modelName = "plain";
    plainProperties.fragmentShaderName = "frag_colorConst";
    plainProperties.color = glm::vec3(0.3f, 0.8f, 0.3f);

    renderer->addObject(DrawableObjectFactory::createObject(plainProperties));



    LightModel defaultLightModel = BLINN;

    ObjectProperties properties;
    properties.bindToLights = true;
    properties.vertexShaderName = "vert_light";

    int x, z, yaw, roll, pitch;
    bool randomizeShader;

    for (auto& param : generatorParameters)
    {
        properties.modelName = param.name;
        properties.scale = glm::vec3(param.scale);
        properties.position.y = param.yOffset;

        if(!param.randomizeShaders)
            properties.fragmentShaderName = getFragmentShaderName(defaultLightModel);

        for (int i = 0; i < param.count; i++)
        {
            properties.position.x = Helper::random(-plainSize, plainSize + 1);
            properties.position.z = Helper::random(-plainSize, plainSize + 1);
            properties.rotation.yaw = Helper::random(0, 360);
            properties.rotation.roll = Helper::random(-param.maxTilt, param.maxTilt + 1);
            properties.rotation.pitch = Helper::random(-param.maxTilt, param.maxTilt + 1);

            if(param.randomizeShaders)
                properties.fragmentShaderName = getFragmentShaderName(lightModels[Helper::random(0, 2) * 2 + 1]);

            renderer->addObject(DrawableObjectFactory::createObject(properties));
        }
    }
    
    

    properties = ObjectProperties();
    properties.modelName = "suzi_smooth";
    properties.vertexShaderName = "vert_light";
    properties.bindToLights = true;
    properties.scale = glm::vec3(0.5f);
    properties.rotation.yaw = 270;
    properties.position.z = 2;
    properties.position.x = 6;

    for(int i = 0; i < 4; i++)
    {
        properties.position.y += properties.scale.y * 2;
        properties.fragmentShaderName = getFragmentShaderName(lightModels[i]);

        renderer->addObject(DrawableObjectFactory::createObject(properties));
    }



    Camera* camera = renderer->getCamera();
    camera->setPosition(glm::vec3(0, 2, 0));
    camera->setRotation(Rotation(90, 90, 0));
    camera->setFlying(false);
}