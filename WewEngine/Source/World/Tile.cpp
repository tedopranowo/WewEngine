#include "Tile.h"

#include "../Actor/Actor.h"
#include "../Actor/ActorComponent.h"

Tile::Tile(const FilePath& filePath, Rect & rect)
    : m_rect(rect)
    , m_isOccupied(false)
{
    m_pTerrain = ResourceCache<Terrain>::Get(filePath);
}

Tile::~Tile()
{
}

void Tile::Draw(Renderer * pRenderer)
{
    m_pTerrain->Draw(pRenderer, m_rect);
}

bool Tile::IsTravelable(Actor * pUnit) const
{
    return m_pTerrain->IsTravelable(pUnit);
}

bool Tile::IsOccupied() const
{
    return m_isOccupied;
}

void Tile::OnActorEnter(Actor * pActor)
{
    m_actorsOnTile.insert(pActor);

    for (const ActorComponent* pComponent : pActor->GetComponents())
    {
        if (pComponent->GetComponentId() == static_cast<int>(ActorComponent::Id::CollisionComponent))
            m_isOccupied = true;
    }
}

void Tile::OnActorExit(Actor * pActor)
{
    for (const ActorComponent* pComponent : pActor->GetComponents())
    {
        if (pComponent->GetComponentId() == static_cast<int>(ActorComponent::Id::CollisionComponent))
            m_isOccupied = false;
    }
    m_actorsOnTile.erase(pActor);
}
