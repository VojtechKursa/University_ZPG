#pragma once

class IViewPortChangedObserver
{
public:
	virtual void viewPortChangedHandler(int width, int height) = 0;
};