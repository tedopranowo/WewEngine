#include "ScriptComponent.h"

#include <Logger.h>
#include <tinyxml2.h>
#include <LuaUtils.h>
#include "../Actor.h"

ScriptComponent::ScriptComponent()
{
}


ScriptComponent::~ScriptComponent()
{
}

void ScriptComponent::Init(tinyxml2::XMLElement * pData, const FilePath & openedFile)
{
    tinyxml2::XMLElement* pFilePathFileData = pData->FirstChildElement("Script");

    if (!pData)
    {
        LOG(Warning, "Cannot find member FilePath at %s", openedFile.GetFullPath());
        return;
    }

    m_scriptFilePath = openedFile;
    m_scriptFilePath.ChangePath(pFilePathFileData->FirstChild()->Value());
}

int ScriptComponent::GetComponentId() const
{
    return static_cast<int>(ActorComponent::Id::ScriptComponent);
}

bool ScriptComponent::CopyData(const ActorComponent * pComponent)
{
    const ScriptComponent* pScriptComponent = dynamic_cast<const ScriptComponent*>(pComponent);
    
    //Check if dynamic cast is success
    if (!pScriptComponent)
    {
        LOG(Warning, "Failed to copy script component");
        return false;
    }

    m_scriptFilePath = pScriptComponent->m_scriptFilePath;

    return true;
}

void ScriptComponent::OnNewTurnStarted()
{
    lua_State* L = luaL_newstate();
    if (luaL_loadfile(L, m_scriptFilePath.GetFullPath().c_str())) {
        LOG(Warning, "Failed to load %s", m_scriptFilePath.GetFullPath().c_str());
        return;
    }

    //Push Move function to lua
    luaL_openlibs(L); // load default Lua libs

    //Create table
    lua_createtable(L, 0, 2);

    //lua push light user data
    lua_pushlightuserdata(L, m_pOwner);
    lua_setfield(L, -2, "this");

    //Push function move
    lua_pushcfunction(L, ScriptComponent::Move);
    lua_setfield(L, -2, "Move");

    lua_setglobal(L, "Logic");

    //Call lua function
    lua_pcall(L, 0, 0, 0);

    lua_getglobal(L, "OnNewTurnStarted");

    //LuaUtils::PrintStack(L);

    lua_pcall(L, 0, 0, 0);

    lua_close(L);

    return;
}

int ScriptComponent::Move(lua_State * pState)
{
    Actor* pActor = static_cast<Actor*>(lua_touserdata(pState, -3));
    int x = static_cast<int>(lua_tonumber(pState, -2));
    int y = static_cast<int>(lua_tonumber(pState, -1));

    lua_pop(pState, 3);

    pActor->Move(Point(x, y));

    return 0;
}
