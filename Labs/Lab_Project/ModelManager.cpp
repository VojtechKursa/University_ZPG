#include "ModelManager.h"

#include "ModelFactory.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4305 )
#endif

#include "Models/models.h"

#ifdef _MSC_VER
#pragma warning( pop )
#endif



std::string ModelManager::names[] = {"plain", "sphere", "suzi_flat", "suzi_smooth", "gift", "bushes", "tree"};
const float* ModelManager::data[] = {plain, sphere, suziFlat, suziSmooth, gift, bushes, tree};
unsigned long ModelManager::sizes[] = {sizeof(plain), sizeof(sphere), sizeof(suziFlat), sizeof(suziSmooth), sizeof(gift), sizeof(bushes), sizeof(tree)};

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
