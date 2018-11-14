#include "StringParser.h"

#include <cctype>

void StringParser::RemoveFrontWhitespace(std::string & text)
{
    const char* textCStr = text.c_str();
    while (textCStr != '\0' && isspace(textCStr[0]))
    {
        textCStr = textCStr + 1;
    }

    text = textCStr;
}

void StringParser::RemoveBackWhitespace(std::string & text)
{
    while (isspace(text.back()))
    {
        text.pop_back();
    }
}
