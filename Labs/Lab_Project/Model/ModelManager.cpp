#include "ModelManager.h"

#include "ModelFactory.h"
#include "ModelLoader.h"

#include "HeaderModelDefinition.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4305 )
#endif

#include "Models/models.h"

#ifdef _MSC_VER
#pragma warning( pop )
#endif



HeaderModelDefinition headerModels[] =
{
    HeaderModelDefinition("plain", plain, POS3_NORM3, sizeof(plain)),
    HeaderModelDefinition("plainTextured", plainTextured, POS3_NORM3_TEX2, sizeof(plainTextured)),
    HeaderModelDefinition("sphere", sphere, POS3_NORM3, sizeof(sphere)),
    HeaderModelDefinition("suzi_flat", suziFlat, POS3_NORM3, sizeof(suziFlat)),
    HeaderModelDefinition("suzi_smooth", suziSmooth, POS3_NORM3, sizeof(suziSmooth)),
    HeaderModelDefinition("gift", gift, POS3_NORM3, sizeof(gift)),
    HeaderModelDefinition("bushes", bushes, POS3_NORM3, sizeof(bushes)),
    HeaderModelDefinition("tree", tree, POS3_NORM3, sizeof(tree)),
    HeaderModelDefinition("skycube", skycube, POS3, sizeof(skycube))
};



ModelManager* ModelManager::instance = new ModelManager();



ModelManager::ModelManager()
{ }

ModelManager *ModelManager::getInstance()
{
    return ModelManager::instance;
}

void ModelManager::loadDefaultModels()
{
    for(int i = 0; i < sizeof(headerModels) / sizeof(headerModels[0]); i++)
    {
        if(this->get(headerModels[i].name) == nullptr)
        {
            this->add(headerModels[i].name, loadDefaultModel(i));
        }
    }
}

Model* ModelManager::loadDefaultModel(int index)
{
    switch(headerModels[index].format)
    {
        case POS3_NORM3_TEX2:
            return ModelFactory::createFrom3Pos3Norm2Tex(headerModels[index].data, headerModels[index].size);
        case POS3:
            return ModelFactory::createFrom3Pos(headerModels[index].data, headerModels[index].size);
        case POS3_NORM3:
        default:
            return ModelFactory::createFrom3Pos3Norm(headerModels[index].data, headerModels[index].size);
    }
}



Model *ModelManager::get(std::string name)
{
    Model* result = Manager::get(name);
    
    if(result != nullptr)
        return result;
    else
    {
        for(int i = 0; i < sizeof(headerModels) / sizeof(headerModels[0]); i++)
        {
            if(name == headerModels[i].name)
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
