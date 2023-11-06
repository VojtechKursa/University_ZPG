#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <opencv2/opencv.hpp>

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

    void importTexture(GLint format, GLsizei rows, GLsizei cols, GLenum type, const void *data);
    void importTexture(cv::Mat& texture);

    bool loadFile(const char* filename);
};