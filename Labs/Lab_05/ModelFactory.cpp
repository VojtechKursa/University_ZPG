#include "ModelFactory.h"

#include "ModelManager.h"
#include "VAO.h"
#include "VBO.h"



Model *ModelFactory::createFrom3Pos3Norm(const float *data, unsigned long length)
{
    VBO* vbo = new VBO();
    vbo->buffer(data, length);

    VAO* vao = new VAO();
    vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);
    vao->enableVertexAttributes(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, sizeof(float) * 3);

    return new Model(vao, length / 6);
}

Model *ModelFactory::createFrom3Pos3Norm(std::string name, const float *data, unsigned long length)
{
    Model* model = ModelFactory::createFrom3Pos3Norm(data, length);
    
    ModelManager::getInstance()->add(name, model);
    
    return model;
}
