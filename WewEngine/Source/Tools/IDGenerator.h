#pragma once

#include <unordered_map>

template<typename T>
class IDGenerator
{
    typedef unsigned int id;    //0 is for invalid id

private:
    std::unordered_map<std::string, id> m_idMap;
    id m_nextId;

public:
    IDGenerator() : m_nextId(1) {}
    ~IDGenerator() { m_idMap.clear(); }
    int GetId(const std::string& text);
};

template<typename T>
inline int IDGenerator<T>::GetId(const std::string& text)
{
    auto found = m_idMap.find(text);

    //If it is not in the map yet
    if (found == m_idMap.end())
    {
        //Add it to the map
        m_idMap.emplace(text, m_nextId);
        ++m_nextId;
    }

    //return the id of the text
    return m_idMap[text];
}

//----------------------------------------------------------------------------------------------
// A base class used for object which want to be converted to Id
//----------------------------------------------------------------------------------------------

template<typename T>
class IDGenerated
{
    static IDGenerator<T> s_idGenerator;
protected:
    int m_id;

public:
    IDGenerated<T>(const std::string& objectString);
};

template<typename T>
IDGenerator<T> IDGenerated<T>::s_idGenerator;

template<typename T>
inline IDGenerated<T>::IDGenerated(const std::string & objectString)
{
    m_id = s_idGenerator.GetId(objectString);
}
