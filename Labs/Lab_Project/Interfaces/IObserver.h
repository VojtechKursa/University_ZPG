#pragma once

#include "../Events/Event.h"

class IObserver
{
public:
    virtual void notify(const Event* event) = 0;
};
