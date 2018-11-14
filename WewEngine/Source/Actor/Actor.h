#pragma once

#include <vector>

#include <SDL_keycode.h>

#include "ActorComponent.h"
#include "../Struct/Point.h"
#include "../Struct/Rect.h"
#include "../Tools/IDGenerator.h"

class World;
class Renderer;
class TransformComponent;

class Actor
{
    friend class ActorFactory;

public:
    class Tag : public IDGenerated<Tag>
    {
    public:
        Tag(const std::string& tagName) : IDGenerated<Tag>(tagName) {}
        bool operator==(const Tag& other) const { return other.m_id == m_id; }
    };

//Variables
private:
    World* m_pWorld;
    std::vector<ActorComponent*> m_actorComponents;
    std::vector<Tag> m_tags;

//Functions
public:
    Actor();
    ~Actor();

    void Draw(Renderer* pRenderer);
    void HandleKeyboardInput(const SDL_Keycode key);
    void OnNewTurnStarted();

    Rect GetRect() const;
    bool Move(const Point& moveDirection);
    void EndTurn();

    //Tag
    void AddTag(const std::string& tagName) { m_tags.emplace_back(tagName); }
    const std::vector<Tag>& GetTags() { return m_tags; }

    //Components
    void AddComponent(ActorComponent* pComponent);
    const std::vector<ActorComponent*>& GetComponents() { return m_actorComponents; }
    TransformComponent* GetTransformComponent();

    //World
    void SetWorld(World* pWorld) { m_pWorld = pWorld; }
    World* GetWorld() { return m_pWorld; }

    //Collision
    bool HasCollisionComponent() const;
};