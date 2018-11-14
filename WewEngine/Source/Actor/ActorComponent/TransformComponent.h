#pragma once

#include "../../Struct/Point.h"
#include "../ActorComponent.h"

class Tile;

class TransformComponent :
    public ActorComponent
{
private:
    Point m_position;

public:
    TransformComponent();
    TransformComponent(const Point& position) : m_position(position) {}
    virtual ~TransformComponent();

    Point GetPosition() const { return m_position; }
    void SetPosition(const Point& position);

    // Inherited via ActorComponent
    virtual void Init(tinyxml2::XMLElement * pData, const FilePath& filePath = FilePath()) override;
    virtual int GetComponentId() const override;
    virtual bool CopyData(const ActorComponent * pComponent) override;

private:
    Tile* GetTile(const Point& position);
};

