#include "ActorFactory.h"

#include <Logger.h>
#include <assert.h>

#include "Actor.h"
#include "ActorComponent/SpriteRenderComponent.h"
#include "ActorComponent/TransformComponent.h"
#include "ActorComponent/ScriptComponent.h"
#include "ActorComponent/PlayerControllerComponent.h"
#include "ActorComponent/CollisionComponent.h"

ActorFactory::ActorFactory()
{
    ConstructInit();
}

ActorFactory::~ActorFactory()
{
    CleanUp();
}

Actor * ActorFactory::CreateActor(const FilePath & filePath)
{
    auto found = m_defaultActors.find(filePath.GetFullPath());

    //If it is not in the cache
    if (found == m_defaultActors.end())
    {
        bool loadSuccess = LoadActor(filePath);
        if (!loadSuccess)
        {
            LOG(Warning, "Failed to load actor from file %s", filePath.GetFullPath().c_str());
            return nullptr;
        }
    }
    
    //Create the copy of the loaded actor
    Actor* pCopiedActor = CreateCopy(m_defaultActors[filePath.GetFullPath()]);

    return pCopiedActor;
}

void ActorFactory::ConstructInit()
{
    //int to component creation func
    //m_intToComponentCreationFunc.emplace_back(&CreateSpriteRenderComponent);
    m_intToComponentCreationFunc.push_back(&CreateSpriteRenderComponent);
    m_intToComponentCreationFunc.push_back(&CreateTransformComponent);
    m_intToComponentCreationFunc.push_back(&CreateScriptComponent);
    m_intToComponentCreationFunc.push_back(&CreatePlayerControllerComponent);
    m_intToComponentCreationFunc.push_back(&CreateCollisionComponent);

    //string to component creation func
    m_stringToComponentCreationFunc.emplace("SpriteRenderComponent", &CreateSpriteRenderComponent);
    m_stringToComponentCreationFunc.emplace("TransformComponent", &CreateTransformComponent);
    m_stringToComponentCreationFunc.emplace("ScriptComponent", &CreateScriptComponent);
    m_stringToComponentCreationFunc.emplace("PlayerControllerComponent", &CreatePlayerControllerComponent);
    m_stringToComponentCreationFunc.emplace("CollisionComponent", &CreateCollisionComponent);

    assert(static_cast<int>(ActorComponent::Id::kCount) == m_intToComponentCreationFunc.size() && static_cast<int>(ActorComponent::Id::kCount) == m_stringToComponentCreationFunc.size());
}

void ActorFactory::CleanUp()
{
    for (auto it = m_defaultActors.begin(); it != m_defaultActors.end(); ++it)
    {
        delete it->second;
        it->second = nullptr;
    }

    m_defaultActors.clear();
    m_intToComponentCreationFunc.clear();
    m_stringToComponentCreationFunc.clear();
}

bool ActorFactory::LoadActor(const FilePath & filePath)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLElement;

    //Load the file
    XMLDocument toLoad;
    toLoad.LoadFile(filePath.GetFullPath().c_str());

    if (toLoad.Error())
    {
        LOG(Warning, "Failed to load %s, %s", filePath.GetFullPath().c_str(), toLoad.ErrorName());
        return false;
    }

    //Start reading the data
    XMLElement* pRoot = toLoad.RootElement();

    if (pRoot == nullptr || std::string(pRoot->Name()) != "Actor")
    {
        LOG(Warning, "Invalid root");
        return false;
    }

    Actor* pNewActor = new Actor();

    //Tag
    XMLElement* pTag = pRoot->FirstChildElement("Tag");
    if(pTag != nullptr)
        pNewActor->AddTag(pTag->FirstChild()->Value());

    //Components
    XMLElement* pComponents = pRoot->FirstChildElement("Components");

    //For every components that is going to be created
    for (auto pActorNode = pComponents->FirstChildElement(); pActorNode; pActorNode = pActorNode->NextSiblingElement())
    {
        ActorComponent* pNewComponent = CreateComponent(pActorNode, filePath);

        if (!pNewComponent)
        {
            LOG(Warning, "Failed to load component %s", pActorNode->Name());
            continue;
        }

        pNewActor->AddComponent(pNewComponent);
    }

    m_defaultActors[filePath.GetFullPath()] = pNewActor;

    return true;
}

Actor * ActorFactory::CreateCopy(Actor * pActor) const
{
    Actor* pNewActor = new Actor();
    pNewActor->m_pWorld = pActor->m_pWorld;
    pNewActor->m_tags = pActor->m_tags;

    for (const ActorComponent* pComponent : pActor->GetComponents())
    {
        //Create new component which is a copy
        int id = pComponent->GetComponentId();
        ActorComponent* pNewComponent = m_intToComponentCreationFunc[id]();
        pNewComponent->CopyData(pComponent);

        //Add the component to the actor
        pNewActor->AddComponent(pNewComponent);
    }

    return pNewActor;
}

ActorComponent * ActorFactory::CreateComponent(tinyxml2::XMLElement * pData, const FilePath& filePath)
{
    //Create the component
    std::string componentName = pData->Name();
    auto pComponentCreationFunc = m_stringToComponentCreationFunc.find(componentName);

    //Check if the component is available
    if (pComponentCreationFunc == m_stringToComponentCreationFunc.end())
    {
        LOG(Warning, "%s is not available in the database", componentName.c_str());
        return nullptr;
    }

    ActorComponent* pNewComponent = pComponentCreationFunc->second();
    
    //Fill in the data
    pNewComponent->Init(pData, filePath);

    return pNewComponent;
}

ActorComponent * ActorFactory::CreateSpriteRenderComponent()
{
    return new SpriteRenderComponent();
}

ActorComponent * ActorFactory::CreateTransformComponent()
{
    return new TransformComponent();
}

ActorComponent * ActorFactory::CreateScriptComponent()
{
    return new ScriptComponent();
}

ActorComponent * ActorFactory::CreatePlayerControllerComponent()
{
    return new PlayerControllerComponent();
}

ActorComponent * ActorFactory::CreateCollisionComponent()
{
    return new CollisionComponent();
}
