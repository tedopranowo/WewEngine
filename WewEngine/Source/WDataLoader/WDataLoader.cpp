#include "WDataLoader.h"

#include <fstream>

#include <StringParser.h>
#include <Logger.h>

WDataLoader::WDataLoader(const FilePath& filePath)
    : m_filePath(filePath)
{
}

WDataLoader::~WDataLoader()
{
}

bool WDataLoader::Load()
{
    std::string fileStr;
    std::string key;
    std::string value;
    std::ifstream inFile;
    inFile.open(m_filePath.GetFullPath());

    //Check if failed to open file
    if (!inFile.is_open())
    {
        LOG(Warning, "Failed to open file %s", m_filePath.GetFullPath().c_str());
        return false;
    }

    //The first line of the file is the object type stored in the file
    std::getline(inFile, fileStr);
    m_objectType = std::move(fileStr);

    //Load the data in the file
    while (!inFile.eof())
    {
        //Get the next line
        std::getline(inFile, fileStr);

        //Find the seperator between key and value
        size_t found = fileStr.find('=');

        //If the seperator is found, it contains the key and value
        if (found != std::string::npos)
        {
            //Push the latest key and value into the map
            AddToFileData(key, value);

            //Get the key
            key = fileStr.substr(0, found);

            //Get the value
            value = fileStr.substr(found + 1);
        }
        //If the seperator is not found, it is the continuation of previous value
        else
        {
            value.append("\n");
            value.append(fileStr);
        }
    }

    //Push the latest key and value into the map
    AddToFileData(key, value);

    inFile.close();

    return true;
}

std::string WDataLoader::operator[](const std::string & key) const
{
    auto find = m_fileData.find(key);

    //If the key is not found
    if (find == m_fileData.end())
        return "";

    //If the key is found
    return find->second;
}

void WDataLoader::AddToFileData(std::string & key, std::string & value)
{
    //Only push to the map if the key isn't empty
    if (key != "")
    {
        StringParser::RemoveFrontWhitespace(key);
        StringParser::RemoveBackWhitespace(key);

        StringParser::RemoveFrontWhitespace(value);
        StringParser::RemoveBackWhitespace(value);
        m_fileData.emplace(key, value);
    }

}
