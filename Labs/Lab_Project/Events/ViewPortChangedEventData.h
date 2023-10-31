#pragma once

#include "EventData.h"

class ViewPortChangedEventData : public EventData
{
public:
    const double newWidth;
    const double newHeight;

    ViewPortChangedEventData(double newWidth, double newHeight)
        : newWidth(newWidth), newHeight(newHeight)
    { }
};
