#include "CubeMapImageMap.h"

CubeMapImageMap::CubeMapImageMap()
{
    map.reserve(6);
}

CubeMapImageMap::CubeMapImageMap(std::string filename_posX, std::string filename_posY, std::string filename_posZ, std::string filename_negX, std::string filename_negY, std::string filename_negZ)
    : CubeMapImageMap()
{
    this->set(CUBEMAP_POS_X, filename_posX);
    this->set(CUBEMAP_POS_Y, filename_posY);
    this->set(CUBEMAP_POS_Z, filename_posZ);
    this->set(CUBEMAP_NEG_X, filename_negX);
    this->set(CUBEMAP_NEG_Y, filename_negY);
    this->set(CUBEMAP_NEG_Z, filename_negZ);
}



bool CubeMapImageMap::isComplete()
{
    const CubeMapPos positions[] = {CUBEMAP_POS_X, CUBEMAP_POS_Y, CUBEMAP_POS_Z, CUBEMAP_NEG_X, CUBEMAP_NEG_Y, CUBEMAP_NEG_Z};

    for(size_t i = 0; i < sizeof(positions) / sizeof(CubeMapPos); i++)
    {
        if(this->map.find(positions[i]) == this->map.end())
            return false;
    }

    return true;
}



void CubeMapImageMap::set(CubeMapPos position, std::string filename)
{
    this->map[position] = filename;
}

std::string CubeMapImageMap::get(CubeMapPos position)
{
    if(this->map.find(position) != this->map.end())
        return this->map[position];
    else
        return "";
}
