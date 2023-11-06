#pragma once

#include "DrawableObject.h"
#include "Texture.h"



class SkyBox : public DrawableObject
{
public:
    SkyBox(Texture* texture);

    virtual void draw() override;
};