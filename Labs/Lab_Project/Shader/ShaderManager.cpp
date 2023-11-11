#include "ShaderManager.h"



ShaderManager* ShaderManager::instance = new ShaderManager();



ShaderManager::ShaderManager()
{
    this->loader = ShaderLoader::getInstance();
}

ShaderManager *ShaderManager::getInstance()
{
    return ShaderManager::instance;
}



Shader *ShaderManager::get(std::string name)
{
    Shader* result = Manager::get(name);

    if(result != nullptr)
        return result;
    
    result = this->loader->addShaderFromFile(name);

    if(result != nullptr)
        this->add(name, result);

    return result;
}
