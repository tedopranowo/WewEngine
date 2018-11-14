#pragma once

#include <FilePath.h>
#include <SDL_keycode.h>

#include "ActorFactory.h"

class ActorManager
{
private:
    std::vector<Actor*> m_actorList;
    ActorFactory m_actorFactory;
    
    World* m_pWorld;

public:
    ActorManager(World* pWorld);
    ~ActorManager();

    void Draw(Renderer* pRenderer);
    bool Load(const FilePath& filePath);
    void HandleKeyboardInput(const SDL_Keycode key);
    void OnNewTurnStarted();
    Actor* GetPlayerActor();
};

