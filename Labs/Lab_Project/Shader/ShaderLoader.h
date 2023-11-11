#pragma once

#include <unordered_map>
#include <string>

#include "Shader.h"



class ShaderLoader
{
private:
    static ShaderLoader* instance;

    const char* directory = "Shaders/";  // path to directory with shaders, WITH trailing slash
    std::unordered_map<std::string, int> extensionTypeMap;

    std::string getFilePath(std::string name, std::string extension);
    
    ShaderLoader();

public:
    static ShaderLoader* getInstance();

    Shader* addShaderFromFile(std::string name);
    Shader* addShaderFromFile(std::string name, std::string extension);
    Shader* addShaderFromFile(std::string name, int type);
};
