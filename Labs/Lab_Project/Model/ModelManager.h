#pragma once

#include "../Manager.h"
#include "Model.h"



class ModelManager : public Manager<Model>
{
private:
    static ModelManager* instance;

    Model* loadDefaultModel(int index);

    ModelManager();
    
public:
    static ModelManager* getInstance();

    void loadDefaultModels();

    virtual Model* get(std::string name) override;
};