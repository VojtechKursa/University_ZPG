#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "../Shader/ShaderProgram.h"



class Texture
{
protected:
    static const std::string textureFolder;

    static GLuint textureUnitsCreated;

    static void setActiveTextureUnit(GLuint unit);

    GLuint textureId;
    GLuint textureUnit;
    GLenum type;

    GLenum wrapping = GL_REPEAT;

public:
    Texture(GLuint textureId, GLenum type);
    Texture(GLuint textureId, GLuint textureUnit, GLenum type);

    void bind();
    void activate();
    bool bindToProgram(ShaderProgram* program);

    static Texture* fromFile(std::string filename, int textureUnit = -1, GLenum type = GL_TEXTURE_2D);
};