#pragma once

#include "EventData.h"

class ViewPortChangedEventData : public EventData
{
public:
    const int newWidth;
    const int newHeight;

    ViewPortChangedEventData(int newWidth, int newHeight)
        : newWidth(newWidth), newHeight(newHeight)
    { }
};
