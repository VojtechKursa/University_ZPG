#include "SkyBox.h"

#include "ModelManager.h"
#include "ShaderManager.h"

#include "Application.h"
#include "Transforms/TransformCameraFollow.h"



SkyBox::SkyBox(CubeMapTexture *texture, Camera* camera)
{
    this->texture = texture;
    this->transformation = new TransformCameraFollow(camera);

    this->model = ModelManager::getInstance()->get("skycube");

    ShaderProgram* program = new ShaderProgram(true, false);
    program->addShader(ShaderManager::getInstance()->get("vert_skybox"));
    program->addShader(ShaderManager::getInstance()->get("frag_skybox"));
    program->link();

    this->shaderProgram = program;

    this->texture->bindToProgram(this->shaderProgram);
}



void SkyBox::draw()
{
    this->texture->activate();

    this->shaderProgram->bindUniform("modelMatrix", this->transformation->getMatrix());
    this->shaderProgram->use();
    
    this->model->draw();
}
