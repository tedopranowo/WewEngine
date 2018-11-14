#pragma once

#include <SDL_keycode.h>

#include "Map.h"
#include "../Actor/ActorManager.h"

class Renderer;
class TurnBasedPuzzleGameLogic;

class World
{
    friend class TurnBasedPuzzleGameLogic;

private:
    Map m_map;
    ActorManager m_actorManager;

    Point m_tileSize;

    //Reference
    TurnBasedPuzzleGameLogic* m_pGameLogic;

public:
    World(TurnBasedPuzzleGameLogic* pGameLogic);
    ~World();

    TurnBasedPuzzleGameLogic* GetGameLogic() { return m_pGameLogic; }
    const Point& GetTileSize() { return m_tileSize; }
    Actor* GetPlayerActor() { return m_actorManager.GetPlayerActor(); }

    // Map
    Map* GetMap() { return &m_map; }

private:
    void Draw(Renderer* pRenderer);
    bool Load(const FilePath& filePath);
    void HandleKeyboardInput(const SDL_Keycode key);
    
    // Tile Size
    void SetTileSize(const Point& tileSize) { m_tileSize = tileSize; }

    // Turn
    void OnNewTurnStarted();
};

