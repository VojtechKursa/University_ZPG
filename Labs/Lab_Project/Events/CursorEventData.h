#pragma once

#include "EventData.h"

class CursorEventData : public EventData
{
public:
    const double x;
    const double y;

    CursorEventData(double x, double y)
        : x(x), y(y)
    { }
};
