#pragma once

#include <vector>

#include "Events/Event.h"
#include "Interfaces/IObserver.h"



class Subject
{
private:
    std::vector<IObserver*> observers;

    long getObserverIndex(IObserver* observer);

protected:
    void notifyAll(const Event* event);

public:
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
};