#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"



class Texture
{
private:
    static GLuint textureUnitsCreated;

    static void setActiveTextureUnit(GLuint unit);

    GLuint textureId;
    GLenum type;

public:
    Texture(GLenum type);
    Texture(GLuint textureId, GLenum type);

    void setActive();
    void bind();

    void bindToProgram(ShaderProgram* program);

    static Texture* fromFile(const char* filename, int textureUnit = -1, GLenum type = GL_TEXTURE_2D);
};