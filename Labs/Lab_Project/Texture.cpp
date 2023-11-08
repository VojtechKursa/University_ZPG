#include "Texture.h"

#include "SOIL/SOIL.h"



GLuint Texture::textureUnitsCreated = 0;



Texture::Texture(GLenum type)
    : Texture(textureUnitsCreated, type)
{ }

Texture::Texture(GLuint textureId, GLenum type)
{
    this->textureId = textureId;
    this->type = type;

    textureUnitsCreated++;
}



void Texture::bind()
{
    glBindTexture(this->type, this->textureId);
}

void Texture::setActive()
{
    glActiveTexture(GL_TEXTURE0 + textureId);;
}



Texture* Texture::fromFile(const char *filename, int textureUnit, GLenum type)
{
    setActiveTextureUnit(textureUnit == -1 ? Texture::textureUnitsCreated : textureUnit);

    GLuint image = SOIL_load_OGL_texture(filename, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (image != 0)
        return new Texture(image, type);
    else
        return nullptr;
}

void Texture::bindToProgram(ShaderProgram *program)
{
    program->bindUniform("textureUnitId", static_cast<int>(this->textureId));
}

void Texture::setActiveTextureUnit(GLuint unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
}
