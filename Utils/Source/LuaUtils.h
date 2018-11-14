#pragma once 
// ------------------------------------- // 
// File Author: Billy (Zesty) Graban 
// Date Created: Fri 04/21/2017 
// ------------------------------------- // 

#include <lua.hpp>
#include <string>

namespace LuaUtils
{
	// Log* functions are meant to display the correct logging data in the
	// console
	void LogStack(lua_State* pState, const char* File, uint32_t Line);
	void LogTopTable(lua_State* pState, const char* File, uint32_t Line,
		std::string &Padding);
	void LogTableRecursive(lua_State* pState, const char* GlobalName, 
		const char* File, uint32_t Line);

	void PrintStack(lua_State* pState);
	void PrintTable(lua_State* pState, std::string &Padding);
	void PrintTableRecursive(lua_State* pState, const char* GlobalName);
}
