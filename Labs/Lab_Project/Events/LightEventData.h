#pragma once

#include "EventData.h"

class Light;

class LightEventData : public EventData
{
public:
    Light* light;

    LightEventData(Light* light)
        : light(light)
    { }
};
