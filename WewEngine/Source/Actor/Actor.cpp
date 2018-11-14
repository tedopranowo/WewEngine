#include "Actor.h"

#include <SDL_render.h>
#include <Logger.h>

#include "ActorComponent/TransformComponent.h"
#include "../World/World.h"
#include "../GameLogic/TurnBasedPuzzleGameLogic.h"

Actor::Actor()
    : m_pWorld(nullptr)
{
}

Actor::~Actor()
{
    for (ActorComponent* pComponent : m_actorComponents)
    {
        delete pComponent;
    }

    m_actorComponents.clear();
}

void Actor::Draw(Renderer * pRenderer)
{
    for (auto& pComponent : m_actorComponents)
    {
        pComponent->Draw(pRenderer);
    }
}

void Actor::HandleKeyboardInput(const SDL_Keycode key)
{
    for (ActorComponent* pComponent : m_actorComponents)
    {
        pComponent->HandleKeyboardInput(key);
    }
}

void Actor::OnNewTurnStarted()
{
    for (ActorComponent* pComponent : m_actorComponents)
    {
        pComponent->OnNewTurnStarted();
    }
}

void Actor::AddComponent(ActorComponent * pComponent)
{
    pComponent->SetOwner(this);
    m_actorComponents.push_back(pComponent);
}

TransformComponent * Actor::GetTransformComponent()
{
    for (ActorComponent* pComponent : m_actorComponents)
    {
        if (pComponent->GetComponentId() == static_cast<int>(ActorComponent::Id::TransformComponent))
        {
            TransformComponent* pTransformComponent = dynamic_cast<TransformComponent*>(pComponent);
            return pTransformComponent;
        }
    }

    return nullptr;
}

bool Actor::HasCollisionComponent() const
{
    for (const ActorComponent* pComponent : m_actorComponents)
    {
        if (pComponent->GetComponentId() == static_cast<int>(ActorComponent::Id::CollisionComponent))
            return true;
    }
    return false;
}

Rect Actor::GetRect() const
{
    for (ActorComponent* pComponent : m_actorComponents)
    {
        if (pComponent->GetComponentId() == static_cast<int>(ActorComponent::Id::TransformComponent))
        {
            const TransformComponent* pTransformComponent = dynamic_cast<const TransformComponent*>(pComponent);
            Point position = pTransformComponent->GetPosition();
            Point tileSize = m_pWorld->GetTileSize();

            return Rect(position.x * tileSize.x, position.y * tileSize.y, tileSize.x, tileSize.y);
        }
    }

    LOG(Warning, "This actor doesn't have a transform component");
    return Rect(0, 0, 0, 0);
}

bool Actor::Move(const Point& moveDirection)
{
    TransformComponent* pTransformComponent = GetTransformComponent();
    Point nextPosition = pTransformComponent->GetPosition() + moveDirection;

    Tile* pTile = m_pWorld->GetMap()->GetTile(nextPosition);

    if (pTile && pTile->IsTravelable(this))
    {
        //If the tile is occupied, don't move
        if (HasCollisionComponent() && pTile->IsOccupied())
            return false;
        
        pTransformComponent->SetPosition(nextPosition);
        return true;
    }

    return false;
}

void Actor::EndTurn()
{
    m_pWorld->GetGameLogic()->EndTurn();
}
