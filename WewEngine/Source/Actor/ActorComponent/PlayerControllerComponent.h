#pragma once

#include "..\ActorComponent.h"

class PlayerControllerComponent :
    public ActorComponent
{
public:
    PlayerControllerComponent();
    virtual ~PlayerControllerComponent();

    // Inherited via ActorComponent
    virtual void Init(tinyxml2::XMLElement * pData, const FilePath & openedFile = FilePath()) override;
    virtual int GetComponentId() const override;
    virtual bool CopyData(const ActorComponent * pComponent) override;

    virtual void HandleKeyboardInput(const SDL_Keycode key) override;
};