#pragma once

#include "../ActorComponent.h"

class CollisionComponent :
    public ActorComponent
{
public:
    CollisionComponent();
    virtual ~CollisionComponent();

    // Inherited via ActorComponent
    virtual void Init(tinyxml2::XMLElement * pData, const FilePath & openedFile = FilePath()) override;
    virtual int GetComponentId() const override;
    virtual bool CopyData(const ActorComponent * pComponent) override;
};

