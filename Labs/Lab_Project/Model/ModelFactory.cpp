#include "ModelFactory.h"

#include "ModelManager.h"
#include "../VAO.h"
#include "../VBO.h"



Model *ModelFactory::createFrom3Pos3Norm(const float *data, unsigned long length)
{
    VBO* vbo = new VBO();
    vbo->buffer(data, length);

    VAO* vao = new VAO();
    vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);
    vao->enableVertexAttributes(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, sizeof(float) * 3);

    return new Model(vao, length / 6);
}

Model *ModelFactory::createFrom3Pos3Norm2Tex(const float *data, unsigned long length)
{
    VBO* vbo = new VBO();
    vbo->buffer(data, length);

    VAO* vao = new VAO();
    vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
    vao->enableVertexAttributes(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 3);
    vao->enableVertexAttributes(vbo, 2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 6);

    return new Model(vao, length / 8);
}

Model *ModelFactory::createFrom3Pos(const float *data, unsigned long length)
{
    VBO* vbo = new VBO();
    vbo->buffer(data, length);

    VAO* vao = new VAO();
    vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    return new Model(vao, length / 3);
}
