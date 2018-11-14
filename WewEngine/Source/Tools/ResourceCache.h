#pragma once

#include <unordered_map>
#include <memory>

#include <FilePath.h>


//-------------------------------------------------------------------------------------------------
// Class ResourceCache
//-------------------------------------------------------------------------------------------------
template<typename T>
class ResourceCache
{
private:
    static std::unordered_map<std::string, std::weak_ptr<T>> m_resourceList;

public:
    //Static class
    ResourceCache() = delete;
    ~ResourceCache() = delete;

    static std::shared_ptr<T> Get(const FilePath& filePath);
};

template<typename T>
std::unordered_map<std::string, std::weak_ptr<T>> ResourceCache<T>::m_resourceList;

template<typename T>
std::shared_ptr<T> ResourceCache<T>::Get(const FilePath & filePath)
{
    auto find = m_resourceList.find(filePath.GetFullPath());

    //If the resource already in the cache and it isn't expired yet, return the cache
    if (find != m_resourceList.end() && !find->second.expired())
        return find->second.lock();

    //Load the resource
    std::shared_ptr<T> resource = std::make_shared<T>();
    resource->Load(filePath);

    //Save the resource into the list
    m_resourceList[filePath.GetFullPath()] = resource;

    return resource;
}

//-------------------------------------------------------------------------------------------------
// Class ICachable
// Class which derived from this class are required to be friend with the resource cache
// Ex: friend class ResourceCache<T>;
//-------------------------------------------------------------------------------------------------
template<typename T>
class ICachable
{
private:
    virtual bool Load(const FilePath& filePath) = 0;
};