#pragma once

#include <Windows.h>
#include <unordered_set>

#include "Color.h"

#define LOG(type, format, ...) Logger::PrintLog(Logger::Type::type, __FILE__, __LINE__, format, __VA_ARGS__)
//#define LOG(type, message, ...) Logger::PrintLog(Logger::Type::)

class Logger
{
public:
    enum class Type : char{
        Info,
        Warning,
        Error,
        Todo,
        kTotalType
    };

private:
    static constexpr Color kLogColor[static_cast<unsigned int>(Type::kTotalType)] =
    {
        Color::Green,
        Color::Yellow,
        Color::Red,
        Color::Purple
    };

///////////////////
// Variables
///////////////////
private:
    static HANDLE s_hConsole;
    static CONSOLE_SCREEN_BUFFER_INFO s_csbi;

    static std::unordered_set<std::string> s_noRepeatPrintList;

///////////////////////////
// Functions
///////////////////////////
public:
    static void PrintLog(Type logType, const char* filePath, const int lineNumber, const char* format, ...);
    static void Print(const char* message, Color color);
    static void PrintNoRepeat(const char* message, Color color);

private:
    static void PrintLogInfo(const char* message);
    static void PrintLogWarning(const char* message, const char* filePath, const int lineNumber);
    static void PrintLogError(const char* message, const char* filePath, const int lineNumber);
    static void PrintLogTodo(const char* message, const char* filePath, const int lineNumber);
};