#pragma once

#include "EventType.h"
#include "EventData.h"

class Event
{
public:
    const EventType eventType;
    const EventData* data;

    Event(EventType eventType, EventData* data)
        : eventType(eventType), data(data)
    { }
};