#include "ModelManager.h"

#include "ModelFactory.h"
#include "ModelLoader.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4305 )
#endif

#include "Models/models.h"

#ifdef _MSC_VER
#pragma warning( pop )
#endif



enum ModelFormat {POS3, POS3_NORM3, POS3_NORM3_TEX2};

std::string ModelManager::names[] = {"plain", "plainTextured", "sphere", "suzi_flat", "suzi_smooth", "gift", "bushes", "tree", "skycube"};
const float* ModelManager::data[] = {plain, plainTextured, sphere, suziFlat, suziSmooth, gift, bushes, tree, skycube};
const ModelFormat formats[] = {POS3_NORM3, POS3_NORM3_TEX2, POS3_NORM3, POS3_NORM3, POS3_NORM3, POS3_NORM3, POS3_NORM3, POS3_NORM3, POS3};
unsigned long ModelManager::sizes[] = {sizeof(plain), sizeof(plainTextured), sizeof(sphere), sizeof(suziFlat), sizeof(suziSmooth), sizeof(gift), sizeof(bushes), sizeof(tree), sizeof(skycube)};

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
            loadDefaultModel(i);
        }
    }
}

Model* ModelManager::loadDefaultModel(int index)
{
    switch(formats[index])
    {
        case POS3_NORM3_TEX2:
            return ModelFactory::createFrom3Pos3Norm2Tex(data[index], sizes[index]);
        case POS3:
            return ModelFactory::createFrom3Pos(data[index], sizes[index]);
        case POS3_NORM3:
        default:
            return ModelFactory::createFrom3Pos3Norm(data[index], sizes[index]);
    }
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
                result = this->loadDefaultModel(i);
                if (result != nullptr)
                    break;
            }
        }
    }

    if(result == nullptr)
        result = ModelLoader::loadModel(name);

    if (result != nullptr)
        this->add(name, result);

    return result;
}
