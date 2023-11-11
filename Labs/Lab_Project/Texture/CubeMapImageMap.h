#pragma once

#include <unordered_map>
#include <string>

#include "CubeMapPos.h"



class CubeMapImageMap
{
private:
    std::unordered_map<CubeMapPos, std::string> map;

public:
    CubeMapImageMap();
    CubeMapImageMap
    (
        std::string filename_posX,
        std::string filename_posY,
        std::string filename_posZ,
        std::string filename_negX,
        std::string filename_negY,
        std::string filename_negZ
    );

    bool isComplete();

    void set(CubeMapPos position, std::string filename);
    std::string get(CubeMapPos position);    
};