#include "Logger.h"

#include <iostream>
#include <sstream>
#include <assert.h>

#include "FilePath.h"

HANDLE Logger::s_hConsole = nullptr;
CONSOLE_SCREEN_BUFFER_INFO Logger::s_csbi;
std::unordered_set<std::string> Logger::s_noRepeatPrintList;

void Logger::PrintLog(Type logType, const char* filePath, const int lineNumber, const char * format, ...)
{
    va_list va;
    char message[128];
    va_start(va, format);
    vsprintf_s(message, format, va);
    va_end(va);

    switch (logType)
    {
    case Type::Info:
        PrintLogInfo(message);
        break;
    case Type::Warning:
        PrintLogWarning(message, filePath, lineNumber);
        break;
    case Type::Error:
        PrintLogError(message, filePath, lineNumber);
        break;
    case Type::Todo:
        PrintLogTodo(message, filePath, lineNumber);
        break;
    case Type::kTotalType:
        assert(0 && "Invalid Log Type");
        break;
    }
}

void Logger::Print(const char * message, Color color)
{
    if (s_hConsole == nullptr)
    {
        s_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    GetConsoleScreenBufferInfo(s_hConsole, &s_csbi);
    SetConsoleTextAttribute(s_hConsole, static_cast<int>(color));
    std::cout << message << std::endl;
    SetConsoleTextAttribute(s_hConsole, s_csbi.wAttributes);
}

void Logger::PrintNoRepeat(const char * message, Color color)
{
    auto itr = s_noRepeatPrintList.find(message);

    //If the message is not in the list, print and add it to the list
    if (itr == s_noRepeatPrintList.end())
    {
        s_noRepeatPrintList.emplace(message);
        Print(message, color);
    }
}

void Logger::PrintLogInfo(const char * message)
{
    std::stringstream outputText;
    outputText << "[Info]: " << message;

    Print(outputText.str().c_str(), kLogColor[static_cast<unsigned int>(Type::Info)]);
}

void Logger::PrintLogWarning(const char * message, const char * filePath, const int lineNumber)
{
    std::stringstream outputText;
    FilePath fullPath(filePath);

    outputText << "[Warning](" << fullPath.GetFileName() << " at line " << lineNumber << "): " << message;
    Print(outputText.str().c_str(), kLogColor[static_cast<unsigned int>(Type::Warning)]);
}

void Logger::PrintLogError(const char * message, const char * filePath, const int lineNumber)
{
    std::stringstream outputText;
    FilePath fullPath(filePath);

    outputText << "[Error](" << fullPath.GetFileName() << " at line " << lineNumber << "): " << message;
    Print(outputText.str().c_str(), kLogColor[static_cast<unsigned int>(Type::Error)]);
}

void Logger::PrintLogTodo(const char * message, const char * filePath, const int lineNumber)
{
    std::stringstream outputText;
    FilePath fullPath(filePath);

    outputText << "[Todo](" << fullPath.GetFileName() << " at line " << lineNumber << "): " << message;
    PrintNoRepeat(outputText.str().c_str(), kLogColor[static_cast<unsigned int>(Type::Todo)]);
}
