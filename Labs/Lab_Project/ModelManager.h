#pragma once

#include "Manager.h"
#include "Model.h"



class ModelManager : public Manager<Model>
{
private:
    static ModelManager* instance;

    static std::string names[];
    static const float* data[];
    static unsigned long sizes[];


    Model* loadDefaultModel(int index);

    ModelManager();
    
public:
    static ModelManager* getInstance();

    void loadDefaultModels();

    virtual Model* get(std::string name) override;
};