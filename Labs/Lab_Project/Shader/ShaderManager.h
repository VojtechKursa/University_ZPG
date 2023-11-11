#pragma once

#include "../Manager.h"
#include "Shader.h"
#include "ShaderLoader.h"



class ShaderManager : public Manager<Shader>
{
private:
    static ShaderManager* instance;

    ShaderLoader* loader;

    ShaderManager();
    
public:
    static ShaderManager* getInstance();

    virtual Shader* get(std::string name) override;
};
