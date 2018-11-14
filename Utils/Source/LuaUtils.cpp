#include "LuaUtils.h" 
// ------------------------------------- // 
// File Author: Billy (Zesty) Graban 
// Date Created: Fri 04/21/2017 
// ------------------------------------- // 

#include "Logger.h"
 
void LuaUtils::PrintStack(lua_State* pState)
{
	int Index;
	int top = lua_gettop(pState);

	LOG(Info, "~~ Printing Stack ~~");
	LOG(Info, "Items in Stack: %d", top);

	for (Index = 1; Index <= top; ++Index)
	{
		int t = lua_type(pState, Index);
		switch (t)
		{
		case LUA_TSTRING:
			LOG(Info, "String: %s", lua_tostring(pState, Index));
			break;
		case LUA_TNUMBER:
			LOG(Info, "Number: %lf", lua_tonumber(pState, Index));
			break;
		default:
			LOG(Info, lua_typename(pState, t));
			break;
		}
	}

	LOG(Info, "~~~~~~~~~~~~~~~~~~");
}

void LuaUtils::PrintTable(lua_State* pState, std::string &Padding)
{
	lua_pushnil(pState);

	// Next pops a key from the stack and pushes a key-value pair from the table
	// at the given index
	while (lua_next(pState, -2) != 0)
	{
		if (lua_isuserdata(pState, -1))
		{
			LOG(Info, "%sUser Data: %s -> %p", Padding.c_str(),
				lua_tostring(pState, -2), lua_touserdata(pState, -1));
		}
		else if (lua_iscfunction(pState, -1))
		{
			LOG(Info, "%sC Function: %s -> %p", Padding.c_str(),
				lua_tostring(pState, -2), (void*)lua_tocfunction(pState, -1));
		}
		else if (lua_isfunction(pState, -1))
		{
			LOG(Info, "%sLua Function: %s", Padding.c_str(),
				lua_tostring(pState, -2));
		}
		else if (lua_isnumber(pState, -1))
		{
			LOG(Info, "%sNumber: %s -> %lf", Padding.c_str(),
				lua_tostring(pState, -2), lua_tonumber(pState, -1));
		}
		else if (lua_isstring(pState, -1))
		{
			LOG(Info, "%sString: %s -> %s", Padding.c_str(),
				lua_tostring(pState, -2), lua_tostring(pState, -1));
		}
		else if (lua_istable(pState, -1))
		{
			// Different printings required to keep things pretty.  It was also
			// the source of the crash I kept encountering.  I think something
			// was going terribly wrong when trying to convert the integer
			// index into a string and use that.  Funny thing is that it would
			// not break right away.  -_-
			if (lua_isinteger(pState, -2))
			{
				LOG(Info, "%s[%d] ->", Padding.c_str(),
					lua_tointeger(pState, -2));
			}
			else if (lua_isstring(pState, -2))
			{
				LOG(Info, "%sTable: %s ->", Padding.c_str(),
					lua_tostring(pState, -2));
			}
			else
			{
				LOG(Warning, "Uknown key type in lua table...");
			}
			
			Padding += "  ";
			PrintTable(pState, Padding);
		}
 		lua_pop(pState, 1);
	}

	if (Padding.size() > 1)
	{
		Padding.erase(Padding.begin(), Padding.begin() + 2);
	}
}

void LuaUtils::LogStack(lua_State* pState, const char* File, uint32_t Line)
{
	int Index;
	int top = lua_gettop(pState);

	LOG(Info, "~~ Printing Stack ~~");
	LOG(Info, "Items in Stack: %d", top);

	for (Index = 1; Index <= top; ++Index)
	{
		int t = lua_type(pState, Index);
		switch (t)
		{
		case LUA_TSTRING:
            LOG(Info, "String: %s", lua_tostring(pState, Index));
			break;
		case LUA_TNUMBER:
            LOG(Info, "Number: %lf", lua_tonumber(pState, Index));
			break;
		default:
            LOG(Info, lua_typename(pState, t));
			break;
		}
	}

    LOG(Info, "~~~~~~~~~~~~~~~~~~~~");
}

void LuaUtils::LogTopTable(lua_State* pState, const char* File, uint32_t Line,
	std::string &Padding)
{
	lua_pushnil(pState);

	// Next pops a key from the stack and pushes a key-value pair from the table
	// at the given index
	while (lua_next(pState, -2) != 0)
	{
		if (lua_isuserdata(pState, -1))
		{
            LOG(Info, "%sUser Data: %s -> %p",
				Padding.c_str(), lua_tostring(pState, -2),
				lua_touserdata(pState, -1));
		}
		else if (lua_iscfunction(pState, -1))
		{
            LOG(Info, "%sC Function: %s -> %p",
				Padding.c_str(), lua_tostring(pState, -2),
				(void*)lua_tocfunction(pState, -1));
		}
		else if (lua_isfunction(pState, -1))
		{
            LOG(Info, "%sLua Function: %s",
				Padding.c_str(), lua_tostring(pState, -2));
		}
		else if (lua_isnumber(pState, -1))
		{
            LOG(Info, "%sNumber: %s -> %lf",
				Padding.c_str(), lua_tostring(pState, -2),
				lua_tonumber(pState, -1));
		}
		else if (lua_isstring(pState, -1))
		{
            LOG(Info, "%sString: %s -> %s",
				Padding.c_str(), lua_tostring(pState, -2),
				lua_tostring(pState, -1));
		}
		else if (lua_istable(pState, -1))
		{
			// Different printings required to keep things pretty.  It was also
			// the source of the crash I kept encountering.  I think something
			// was going terribly wrong when trying to convert the integer
			// index into a string and use that.  Funny thing is that it would
			// not break right away.  -_-
			if (lua_isinteger(pState, -2))
			{
                LOG(Info, "%s[%d] ->", Padding.c_str(),
					lua_tointeger(pState, -2));
			}
			else if (lua_isstring(pState, -2))
			{
                LOG(Info, "%sTable: %s ->",
					Padding.c_str(), lua_tostring(pState, -2));
			}
			else
			{
                LOG(Info,
					"Uknown key type in lua table...");
			}

			Padding += "  ";
			LogTopTable(pState, File, Line, Padding);
		}
		lua_pop(pState, 1);
	}

	if (Padding.size() > 1)
	{
		Padding.erase(Padding.begin(), Padding.begin() + 2);
	}
}

void LuaUtils::LogTableRecursive(lua_State * pState, const char * GlobalName,
	const char* File, uint32_t Line)
{
	std::string Padding = "";
	lua_getglobal(pState, GlobalName);

	// Begin Table
    LOG(Info, "Printing Table Recursively: %s",
		GlobalName);

	LogTopTable(pState, File, Line, Padding);

	// End Table
    LOG(Info, "---- %s Table Complete ----", GlobalName);

	lua_pop(pState, 1);
}

void LuaUtils::PrintTableRecursive(lua_State * pState, const char * GlobalName)
{
	std::string Padding = "";
	lua_getglobal(pState, GlobalName);

    LOG(Info, "Printing Table Recursively: %s", GlobalName);
	PrintTable(pState, Padding);
    LOG(Info, "---- %s Table Complete ----", GlobalName);

	lua_pop(pState, 1);
}
