#pragma once

#include <string>

#include "Renderer.h"



enum LightModel
{
    CONST,
    LAMBERT,
    PHONG,
    BLINN
};



class SceneLoader
{
private:
    static std::string getFragmentShaderName(LightModel lightModel);

    static const LightModel lightModels[];
    static const int lightModelsCount;

public:
    static void loadDefault3DScene(Renderer* renderer);
    static void loadLightsDemoScene(Renderer* renderer);

    static void loadSphereWithLight(Renderer* renderer, LightModel lightModel);
    static void loadSpheresWithLight(Renderer* renderer, LightModel lightModel);

    static void loadForest(Renderer* renderer);
};
