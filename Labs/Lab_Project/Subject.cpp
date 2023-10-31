#include "Subject.h"



long Subject::getObserverIndex(IObserver *observer)
{
    for(long i = 0; i < observers.size(); i++)
    {
        if(observers[i] == observer)
            return i;
    }
    
    return -1;
}

void Subject::notifyAll(const Event *event)
{
    for(auto obs : this->observers)
    {
        obs->notify(event);
    }
}

void Subject::registerObserver(IObserver *observer)
{
    if(this->getObserverIndex(observer) == -1)
    {
        this->observers.push_back(observer);
    }
}

void Subject::unregisterObserver(IObserver *observer)
{
    int index = getObserverIndex(observer);

    if(index != -1)
    {
        this->observers.erase(this->observers.begin() + index);
    }
}
