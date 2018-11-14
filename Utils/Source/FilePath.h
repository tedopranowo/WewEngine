#pragma once

#include <string>

class FilePath
{
private:
    std::string m_directory;
    std::string m_fileName;

public:
    FilePath() {}
    FilePath(const std::string& fullPath);
    FilePath(const char* fullPath);
    ~FilePath();

    void ChangePath(std::string relativePath);

    std::string GetDirectory() const { return m_directory; }
    std::string GetFileName() const { return m_fileName; }
    std::string GetFullPath() const { return m_directory + m_fileName; }

    void MoveUp();

private:
    void Parse(std::string fullPath);
    void BackSlashToForwardSlash(std::string& fullPath);
};

