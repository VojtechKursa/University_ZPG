#pragma once

#include "EventData.h"

class FrameEventData : public EventData
{
public:
    const double timeSinceLastFrameSec;

    FrameEventData(double timeSinceLastFrameSec)
        : timeSinceLastFrameSec(timeSinceLastFrameSec)
    { }
};
