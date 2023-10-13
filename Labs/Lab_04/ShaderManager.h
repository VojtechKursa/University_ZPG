#pragma once

#include <unordered_map>

#include "Manager.h"
#include "Shader.h"



class ShaderManager : public Manager<Shader>
{
private:
    static ShaderManager* instance;

    const char* directory = "shaders/";  // path to directory with shaders, WITH trailing slash
    std::unordered_map<std::string, int> extensionTypeMap;

    std::string getFilePath(std::string name, std::string extension);
    
    Shader* addShaderFromFile(std::string name);
    Shader* addShaderFromFile(std::string name, std::string extension);
    Shader* addShaderFromFile(std::string name, int type);

    ShaderManager();
    
public:
    static ShaderManager* getInstance();

    virtual Shader* get(std::string name) override;
};