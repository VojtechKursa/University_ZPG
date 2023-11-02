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
    static void loadRotatingSquare(Renderer* renderer);
    static void loadContinuousMovementDemo(Renderer* renderer);
    static void loadSolarSystem(Renderer* renderer);

    static void loadDefault3DScene(Renderer* renderer);
    static void loadLightsDemoScene(Renderer* renderer);

    static void loadSphereWithLight(Renderer* renderer, LightModel lightModel);
    static void loadSpheresWithLight(Renderer* renderer, LightModel lightModel);

    static void loadSpotlightTest(Renderer* renderer);

    static void loadForest(Renderer* renderer);
};
