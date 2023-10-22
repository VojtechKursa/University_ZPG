#pragma once

class IFrameObserver
{
public:
    virtual void frameHandler(double timeSinceLastFrameSec) = 0;
};