#include "CubeMapTexture.h"

#include "SOIL/SOIL.h"



CubeMapTexture::CubeMapTexture(GLuint textureId)
    : Texture(textureId, GL_TEXTURE_CUBE_MAP)
{ }



CubeMapTexture *CubeMapTexture::fromFile(CubeMapImageMap &imageMap, int textureUnit)
{
    if(!imageMap.isComplete())
        return nullptr;

    setActiveTextureUnit(textureUnit == -1 ? Texture::textureUnitsCreated : textureUnit);

    GLuint image = SOIL_load_OGL_cubemap
    (
        (Texture::textureFolder + imageMap.get(CUBEMAP_POS_X)).c_str(),
        (Texture::textureFolder + imageMap.get(CUBEMAP_NEG_X)).c_str(),
        (Texture::textureFolder + imageMap.get(CUBEMAP_POS_Y)).c_str(),
        (Texture::textureFolder + imageMap.get(CUBEMAP_NEG_Y)).c_str(),
        (Texture::textureFolder + imageMap.get(CUBEMAP_POS_Z)).c_str(),
        (Texture::textureFolder + imageMap.get(CUBEMAP_NEG_Z)).c_str(),
        SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0
    );

    if (image != 0)
        return new CubeMapTexture(image);
    else
        return nullptr;
}