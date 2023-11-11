#pragma once

#include "Texture.h"
#include "CubeMapImageMap.h"



class CubeMapTexture : public Texture
{
protected:
    CubeMapTexture(GLuint textureId);

public:
    static CubeMapTexture* fromFile(CubeMapImageMap& imageMap, int textureUnit = -1);
};