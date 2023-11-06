#include "Texture.h"



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



bool Texture::loadFile(const char *filename)
{
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);

    if(!image.data)
        return false;
    
    cv::Mat imageFlipped;
    cv::flip(image, imageFlipped, 0);

    this->importTexture(image);

    return true;
}

void Texture::bindToProgram(ShaderProgram *program)
{
    program->bindUniform("textureUnitId", static_cast<int>(this->textureId));
}

void Texture::importTexture(GLint format, GLsizei rows, GLsizei cols, GLenum type, const void* data)
{
    this->setActive();

    glTexImage2D(this->type, 0, format, rows, cols, 0, format, type, data);
}

void Texture::importTexture(cv::Mat& texture)
{
    GLint format;

    switch(texture.channels())
    {
        case 4:
            format = GL_RGBA;
            break;
        case 3:
        default:
            format = GL_RGB;
            break;
    }

    this->importTexture(format, texture.rows, texture.cols, GL_BYTE, texture.data);
}

void Texture::setActiveTextureUnit(GLuint unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
}
