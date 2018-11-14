#pragma once

#include <string>

class StringParser
{
public:
    StringParser() = delete;
    ~StringParser() = delete;

    static void RemoveFrontWhitespace(std::string& text);
    static void RemoveBackWhitespace(std::string& text);
};
