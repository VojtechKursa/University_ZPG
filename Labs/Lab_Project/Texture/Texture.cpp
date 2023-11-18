#include "Texture.h"

#include "SOIL/SOIL.h"



GLuint Texture::textureUnitsCreated = 0;

const std::string Texture::textureFolder = "Assets/Textures/";



Texture::Texture(GLuint textureId, GLenum type)
{
    this->textureId = textureId;
    this->type = type;
    this->textureUnit = textureUnitsCreated;

    textureUnitsCreated++;
}

Texture::Texture(GLuint textureId, GLuint textureUnit, GLenum type)
{
    this->textureId = textureId;
    this->type = type;
    this->textureUnit = textureUnit;

    Texture::textureUnitsCreated = this->textureUnit + 1;
}



void Texture::bind()
{
    glBindTexture(this->type, this->textureId);
}

void Texture::activate()
{
    Texture::setActiveTextureUnit(this->textureUnit);
    this->bind();
}

bool Texture::bindToProgram(ShaderProgram* program)
{
    return program->bindUniform("textureUnitId", static_cast<int>(this->textureUnit));
}



Texture* Texture::fromFile(std::string filename, int textureUnit, GLenum type)
{
    setActiveTextureUnit(textureUnit == -1 ? Texture::textureUnitsCreated : textureUnit);

    GLuint image = SOIL_load_OGL_texture((textureFolder + filename).c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (image != 0)
        return new Texture(image, type);
    else
        return nullptr;
}



void Texture::setActiveTextureUnit(GLuint unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
}
