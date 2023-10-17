#pragma once

#include <unordered_map>
#include <string>



template <typename T>
class Manager
{
private:
    std::unordered_map<std::string, T*> storage;
    
public:
    virtual void add(std::string name, T* item);
    virtual T* get(std::string name);
    virtual bool remove(std::string name);
};



template <typename T>
inline void Manager<T>::add(std::string name, T* item)
{
    this->storage.emplace(name, item);
}

template <typename T>
inline T* Manager<T>::get(std::string name)
{
    auto iterator = this->storage.find(name);

    if(iterator == this->storage.end())
        return nullptr;
    else
        return iterator->second;
}

template <typename T>
inline bool Manager<T>::remove(std::string name)
{
    return this->storage.erase(name);
}
