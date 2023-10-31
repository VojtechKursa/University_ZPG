#pragma once

#include "EventData.h"

class KeyEventData : public EventData
{
public:
    const int key;
    const int scanCode;
    const int action;
    const int mods;

    KeyEventData(int key, int scanCode, int action, int mods)
        : key(key), scanCode(scanCode), action(action), mods(mods)
    { }
};
