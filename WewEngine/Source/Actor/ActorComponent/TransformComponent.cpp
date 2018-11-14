#include "TransformComponent.h"

#include <Logger.h>

#include "../ActorFactory.h"
#include "../../World/World.h"

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetPosition(const Point & position)
{
    //Remove this actor from the previous tile
    GetTile(m_position)->OnActorExit(m_pOwner);

    m_position = position;

    //Add this actor to the new tile
    GetTile(m_position)->OnActorEnter(m_pOwner);

}

void TransformComponent::Init(tinyxml2::XMLElement * pData, const FilePath& filePath)
{
    LOG(Todo, "Implement TransformComponent::Init");
}

int TransformComponent::GetComponentId() const
{
    return static_cast<int>(Id::TransformComponent);
}

bool TransformComponent::CopyData(const ActorComponent * pComponent)
{
    LOG(Todo, "Impelment TransformComponent::CopyData");
    return false;
}

Tile * TransformComponent::GetTile(const Point & position)
{
    return m_pOwner->GetWorld()->GetMap()->GetTile(position);
}
