#pragma once

#include "EventData.h"

class MouseButtonEventData : public EventData
{
public:
    const int button;
    const int action;
    const int mode;

    MouseButtonEventData(int button, int action, int mode)
        : button(button), action(action), mode(mode)
    { }
};
