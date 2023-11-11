#pragma once

#include "DrawableObject.h"
#include "Texture/CubeMapTexture.h"



class SkyBox : public DrawableObject
{
private:
    CubeMapTexture* texture;

public:
    SkyBox(CubeMapTexture* texture, Camera* camera);

    virtual void draw() override;
};