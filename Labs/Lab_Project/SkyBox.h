#pragma once

#include "DrawableObject.h"
#include "Texture/CubeMapTexture.h"



class SkyBox : public DrawableObject
{
private:
    CubeMapTexture* texture;
    float brightness;

public:
    SkyBox(CubeMapTexture* texture, Camera* camera, float brightness = 1.0f);

    virtual void draw() override;
};