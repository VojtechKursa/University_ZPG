#include "SceneLoader.h"

#include "DrawableObjectFactory.h"



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

void SceneLoader::loadDefault3DScene(Renderer* renderer)
{
    renderer->addObject(DrawableObjectFactory::createDefaultSphere());
	renderer->addObject(DrawableObjectFactory::createDefaultSmoothSuzi());
	renderer->addObject(DrawableObjectFactory::createDefaultFlatSuzi());

	renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(0, 0, -2), Rotation(), glm::vec3(1.f), "suzi_smooth"));
}

void SceneLoader::loadLightsDemoScene(Renderer* renderer)
{
    renderer->addLight(DrawableObjectFactory::createLight(glm::vec3(0,0,3)));

    renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(2,0,3), Rotation(), glm::vec3(0.7f), "sphere", "vert_light", getFragmentShaderName(CONST), true));
	renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(-2,0,3), Rotation(90,0,0), glm::vec3(0.7f), "suzi_smooth", "vert_light", getFragmentShaderName(CONST), true));

    renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(2,0,6), Rotation(), glm::vec3(0.7f), "sphere", "vert_light", getFragmentShaderName(LAMBERT), true));
	renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(-2,0,6), Rotation(90,0,0), glm::vec3(0.7f), "suzi_smooth", "vert_light", getFragmentShaderName(LAMBERT), true));

    renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(2,0,9), Rotation(), glm::vec3(0.7f), "sphere", "vert_light", getFragmentShaderName(PHONG), true));
	renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(-2,0,9), Rotation(90,0,0), glm::vec3(0.7f), "suzi_smooth", "vert_light", getFragmentShaderName(PHONG), true));

    renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(2,0,12), Rotation(), glm::vec3(0.7f), "sphere", "vert_light", getFragmentShaderName(BLINN), true));
	renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(-2,0,12), Rotation(90,0,0), glm::vec3(0.7f), "suzi_smooth", "vert_light", getFragmentShaderName(BLINN), true));

    Camera* camera = renderer->getCamera();
    camera->setPosition(glm::vec3(0,3,0));
    camera->setRotation(Rotation(90, 120, 0));
}

void SceneLoader::loadSphereWithLight(Renderer* renderer, LightModel lightModel)
{
    renderer->addLight(DrawableObjectFactory::createLight(glm::vec3(0, 0, 8)));

    renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(0, 0, 4), Rotation(), glm::vec3(0.5f), "sphere", "vert_light", getFragmentShaderName(lightModel), true));
}

void SceneLoader::loadSpheresWithLight(Renderer* renderer, LightModel lightModel)
{
    renderer->addLight(DrawableObjectFactory::createLight());

    std::string fragShaderName = getFragmentShaderName(lightModel);

	const int pos[8] = {
		0,	2,
		2,	0,
		0,	-2,
		-2,	0
	};

	for(int i = 0; i < 8; i+=2)
	{
		renderer->addObject(DrawableObjectFactory::createObject(glm::vec3(pos[i], 0, pos[i+1]), Rotation(), glm::vec3(1.f), "sphere", "vert_light", fragShaderName, true));
	}

    Camera* camera = renderer->getCamera();
	camera->setPosition(glm::vec3(0,8,0));
	camera->setRotation(Rotation(90,179.9f,0));
}