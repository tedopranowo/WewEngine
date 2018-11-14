#pragma once

#include <unordered_set>

#include "Terrain.h"
#include "../Struct/Rect.h"

class Actor;

class Tile
{
private:
    std::shared_ptr<Terrain> m_pTerrain;
    std::unordered_set<Actor*> m_actorsOnTile;
    Rect m_rect;
    bool m_isOccupied;

public:
    Tile(const FilePath& filePath, Rect& rect);
    ~Tile();

    const Rect& GetRect() { return m_rect; }
    void Draw(Renderer* pRenderer);

    bool IsTravelable(Actor* pUnit) const;
    bool IsOccupied() const;

    //Actor
    void OnActorEnter(Actor* pActor);
    void OnActorExit(Actor* pActor);
};