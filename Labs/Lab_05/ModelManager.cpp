#include "ModelManager.h"

#include "ModelFactory.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4305 )
#endif

#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "sphere.h"

#ifdef _MSC_VER
#pragma warning( pop )
#endif



std::string ModelManager::names[] = {"suzi_flat", "suzi_smooth", "sphere"};
const float* ModelManager::data[] = {suziFlat, suziSmooth, sphere};
unsigned long ModelManager::sizes[] = {sizeof(suziFlat), sizeof(suziSmooth), sizeof(sphere)};

ModelManager* ModelManager::instance = new ModelManager();



ModelManager::ModelManager()
{ }

ModelManager *ModelManager::getInstance()
{
    return ModelManager::instance;
}

void ModelManager::loadDefaultModels()
{
    for(int i = 0; i < sizeof(names) / sizeof(names[0]); i++)
    {
        if(this->get(this->names[i]) == nullptr)
        {
            ModelFactory::createFrom3Pos3Norm(names[i], data[i], sizes[i]);
        }
    }
}

Model* ModelManager::loadDefaultModel(int index)
{
    return ModelFactory::createFrom3Pos3Norm(names[index], data[index], sizes[index]);
}



Model *ModelManager::get(std::string name)
{
    Model* result = Manager::get(name);
    
    if(result != nullptr)
        return result;
    else
    {
        for(int i = 0; i < sizeof(this->names) / sizeof(this->names[0]); i++)
        {
            if(name == this->names[i])
            {
                return this->loadDefaultModel(i);
            }
        }
    }

    return result;
}
