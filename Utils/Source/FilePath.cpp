#include "FilePath.h"

#include <algorithm>

#include "StringParser.h"

FilePath::FilePath(const std::string & fullPath)
{
    Parse(fullPath);
}

FilePath::FilePath(const char * fullPath)
{
    Parse(fullPath);
}

FilePath::~FilePath()
{
}

void FilePath::ChangePath(std::string relativePath)
{
    //Convert backslash to forward slash
    BackSlashToForwardSlash(relativePath);

    //Move up from the current directory for every "../" found
    while (relativePath.substr(0, 3) == "../")
    {
        MoveUp();
        relativePath = relativePath.substr(3);
    }

    //Get the file name
    size_t foundIndex = relativePath.find_last_of('/');
    if (foundIndex == std::string::npos)
    {
        m_fileName = relativePath;
        return;
    }

    m_fileName = relativePath.substr(foundIndex + 1);

    //Update the directory
    relativePath = relativePath.substr(0, foundIndex + 1);
    m_directory += relativePath;
}

void FilePath::MoveUp()
{
    //Set file name to empty
    m_fileName = "";

    //remove the last '/'
    m_directory.pop_back();     

    //remove text from back until '/' sign
    size_t foundIndex = m_directory.find_last_of('/');
    m_directory = m_directory.substr(0, foundIndex + 1);
}

void FilePath::Parse(std::string fullPath)
{
    BackSlashToForwardSlash(fullPath);
    size_t foundIndex = fullPath.find_last_of('/');

    m_directory = fullPath.substr(0, foundIndex + 1);
    m_fileName = fullPath.substr(foundIndex + 1);
}

void FilePath::BackSlashToForwardSlash(std::string & fullPath)
{
    for (size_t foundIndex = fullPath.find('\\'); foundIndex != std::string::npos; foundIndex = fullPath.find('\\'))
    {
        fullPath[foundIndex] = '/';
    }
}
