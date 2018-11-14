#pragma once

#include "..\ActorComponent.h"
#include <lua.hpp>

class ScriptComponent :
    public ActorComponent
{
private:
    FilePath m_scriptFilePath;

public:
    ScriptComponent();
    virtual ~ScriptComponent();

    // Inherited via ActorComponent
    virtual void Init(tinyxml2::XMLElement * pData, const FilePath & openedFile = FilePath()) override;
    virtual int GetComponentId() const override;
    virtual bool CopyData(const ActorComponent * pComponent) override;
    virtual void OnNewTurnStarted() override;

public:
    static int Move(lua_State* pState);
};