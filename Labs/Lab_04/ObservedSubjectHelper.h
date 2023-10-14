#pragma once

#include <vector>



class ObservedSubjectHelper
{
public:
    template<typename T>
    static bool registerObserver(std::vector<T*>& observers, T* observer);

    template<typename T>
    static bool unregisterObserver(std::vector<T*>& observers, T* observer);
};



template<typename T>
bool ObservedSubjectHelper::registerObserver(std::vector<T*>& observers, T* observer)
{
    if(observer != nullptr)
    {
        observers.push_back(observer);
        return true;
    }

    return false;
}

template<typename T>
bool ObservedSubjectHelper::unregisterObserver(std::vector<T*>& observers, T* observer)
{
    if (observer != nullptr)
    {
        for (int i = 0; i < observers.size(); i++)
        {
            if (observers[i] == observer)
            {
                observers.erase(observers.begin() + i);
                return true;
            }
        }
    }

    return false;
}