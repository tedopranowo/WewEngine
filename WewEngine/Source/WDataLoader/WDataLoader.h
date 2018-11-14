#pragma once

#include <unordered_map>

#include <FilePath.h>

class WDataLoader
{
    typedef std::string Key;
    typedef std::string Value;

private:
    FilePath m_filePath;
    std::string m_objectType;
    std::unordered_map<Key, Value> m_fileData;

public:
    WDataLoader(const FilePath& filePath);
    ~WDataLoader();

    bool Load();

    const FilePath& GetFilePath() const { return m_filePath; }
    const std::string& GetObjectType() const { return m_objectType; }
    
    std::string operator[](const std::string& key) const;

private:
    void AddToFileData(std::string& key, std::string& value);
};

