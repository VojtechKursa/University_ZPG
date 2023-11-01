#pragma once

#include "LightEventData.h"
#include "../LightStruct.h"



class LightCountEventData : public LightEventData
{
public:
    const bool added;
    const int index;
    const LightStruct_t lightStruct;
    
    LightCountEventData(Light* light, bool added, int index, LightStruct_t lightStruct)
        : LightEventData(light), added(added), index(index), lightStruct(lightStruct)
    { }
};
