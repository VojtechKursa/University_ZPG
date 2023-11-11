#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Shader/ShaderProgram.h"



class Texture
{
protected:
    static GLuint textureUnitsCreated;

    static void setActiveTextureUnit(GLuint unit);

    GLuint textureId;
    GLuint textureUnit;
    GLenum type;

public:
    Texture(GLuint textureId, GLenum type);
    Texture(GLuint textureId, GLuint textureUnit, GLenum type);

    void bind();
    void activate();
    bool bindToProgram(ShaderProgram* program);

    static Texture* fromFile(const char* filename, int textureUnit = -1, GLenum type = GL_TEXTURE_2D);
};