#pragma once

class Light;

class ILightObserver
{
public:
	virtual void lightChangedHandler(Light* light) = 0;
};