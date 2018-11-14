#pragma once

#include <unordered_map>
#include <memory>
#include <FilePath.h>
#include <tinyxml2.h>

#include "Actor.h"

class ActorFactory
{
private:
    typedef ActorComponent*(*ActorFactory::ComponentCreationFunc)();

public:
//////////////////////////
// Variable
//////////////////////////
private:
    std::unordered_map<std::string, Actor*> m_defaultActors;

    //Conversion data
    std::vector<ComponentCreationFunc> m_intToComponentCreationFunc;
    std::unordered_map<std::string, ComponentCreationFunc> m_stringToComponentCreationFunc;

//////////////////////////
// Function
//////////////////////////
public:
    ActorFactory();
    ~ActorFactory();

    Actor* CreateActor(const FilePath& filePath);

private:
    void ConstructInit();
    void CleanUp();

    //Actors
    bool LoadActor(const FilePath& filePath);
    Actor* CreateCopy(Actor* pActor) const;

    //Components
    ActorComponent* CreateComponent(tinyxml2::XMLElement* pData, const FilePath& filePath);

    static ActorComponent* CreateSpriteRenderComponent();
    static ActorComponent* CreateTransformComponent();
    static ActorComponent* CreateScriptComponent();
    static ActorComponent* CreatePlayerControllerComponent();
    static ActorComponent* CreateCollisionComponent();
};