#include "CollisionComponent.h"

#include <Logger.h>

CollisionComponent::CollisionComponent()
{
}


CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::Init(tinyxml2::XMLElement * pData, const FilePath & openedFile)
{
    //We don't need to do anything here
}

int CollisionComponent::GetComponentId() const
{
    return static_cast<int>(ActorComponent::Id::CollisionComponent);
}

bool CollisionComponent::CopyData(const ActorComponent * pComponent)
{
    //We don't need to do anything here
    return true;
}
