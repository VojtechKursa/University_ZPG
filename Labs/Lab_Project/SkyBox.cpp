#include "SkyBox.h"

#include "ModelManager.h"
#include "ShaderManager.h"



SkyBox::SkyBox(Texture *texture)
{
    this->model = ModelManager::getInstance()->get("skycube");

    ShaderProgram* program = new ShaderProgram(true, false);
    program->addShader(ShaderManager::getInstance()->get("vert_skybox"));
    program->addShader(ShaderManager::getInstance()->get("frag_skybox"));
    program->link();

    texture->bindToProgram(program);

    this->shaderProgram = program;
}

void SkyBox::draw()
{
    this->shaderProgram->bindUniform("modelMatrix", glm::identity<glm::mat4>());
    this->shaderProgram->use();
    
    this->model->draw();
}
