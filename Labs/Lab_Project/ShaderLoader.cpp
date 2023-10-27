#include "ShaderLoader.h"

#include <sys/types.h>
#include <sys/stat.h>

#ifndef _MSC_VER
#include <unistd.h>
#endif



ShaderLoader* ShaderLoader::instance = new ShaderLoader();



ShaderLoader::ShaderLoader()
{
    this->extensionTypeMap.emplace("vert", GL_VERTEX_SHADER);
    this->extensionTypeMap.emplace("frag", GL_FRAGMENT_SHADER);
}



ShaderLoader *ShaderLoader::getInstance()
{
    return ShaderLoader::instance;
}



std::string ShaderLoader::getFilePath(std::string name, std::string extension)
{
    return this->directory + name + "." + extension;
}

Shader *ShaderLoader::addShaderFromFile(std::string name)
{
    Shader* result;

    for(auto& p : this->extensionTypeMap)
    {
        result = this->addShaderFromFile(name, p.first);

        if(result != nullptr)
            return result;
    }

    return nullptr;
}

Shader *ShaderLoader::addShaderFromFile(std::string name, std::string extension)
{
    int type;
    {
        auto typeIterator = this->extensionTypeMap.find(extension);
        if(typeIterator == this->extensionTypeMap.end())
            return nullptr; // cannot determine shader type based on extension
        else
            type = typeIterator->second;
    }

    struct stat st;
    if (stat(this->getFilePath(name, extension).c_str(), &st) == -1)
        return nullptr; // file doesn't exist or program doesn't have access to it
    
    off_t length = st.st_size;

    FILE* file;
    if((file = fopen((this->directory + name + "." + extension).c_str(), "rb")) != NULL)
    {
        char* buffer = new char[length + 1];
        fread(buffer, length, 1, file);
        buffer[length] = 0;

        Shader* shader = new Shader(type, buffer);

        return shader;
    }
    else
        return nullptr;     // failed to open the file
}

Shader *ShaderLoader::addShaderFromFile(std::string name, int type)
{
    for(auto& p : this->extensionTypeMap)
    {
        if(p.second == type)
        {
            return this->addShaderFromFile(name, p.first);
        }
    }

    return nullptr;
}
