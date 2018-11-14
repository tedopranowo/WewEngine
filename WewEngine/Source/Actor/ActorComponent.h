#pragma once

#include <tinyxml2.h>
#include <FilePath.h>
#include <SDL_keycode.h>

class Renderer;
class Actor;

class ActorComponent
{
public:
    enum class Id
    {
        SpriteRenderComponent,
        TransformComponent,
        ScriptComponent,
        PlayerControllerComponent,
        CollisionComponent,
        kCount
    };

protected:
    Actor* m_pOwner;

public:
    ActorComponent();
    virtual ~ActorComponent();

    void SetOwner(Actor* pOwner) { m_pOwner = pOwner; }

    virtual void Init(tinyxml2::XMLElement* pData, const FilePath& openedFile = FilePath()) = 0;
    virtual void Draw(Renderer* pRenderer) {}
    virtual void HandleKeyboardInput(const SDL_Keycode key) {}
    virtual void OnNewTurnStarted() {}
    virtual int GetComponentId() const = 0;
    virtual bool CopyData(const ActorComponent* pComponent) = 0;
};

