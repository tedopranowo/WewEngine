#include "ActorManager.h"

#include <tinyxml2.h>
#include <Logger.h>

#include "ActorFactory.h"
#include "ActorComponent\TransformComponent.h"

ActorManager::ActorManager(World* pWorld)
    : m_pWorld(pWorld)
{
}


ActorManager::~ActorManager()
{
    for (Actor* pActor : m_actorList)
    {
        delete pActor;
    }
    m_actorList.clear();
}

void ActorManager::Draw(Renderer * pRenderer)
{
    for (auto pActor : m_actorList)
    {
        pActor->Draw(pRenderer);
    }
}

bool ActorManager::Load(const FilePath & filePath)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLElement;

    //Load the file
    XMLDocument toLoad;
    toLoad.LoadFile(filePath.GetFullPath().c_str());

    if (toLoad.Error())
    {
        LOG(Error, "Failed to load %s", filePath.GetFullPath().c_str());
        return false;
    }

    //Start reading the data
    XMLElement* pRoot = toLoad.RootElement();

    if (pRoot == nullptr || std::string(pRoot->Name()) != "ActorList")
    {
        LOG(Error, "Invalid root %s", pRoot->Name());
        return false;
    }

    //For every actor that is going to be created
    for (auto pActorNode = pRoot->FirstChildElement(); pActorNode; pActorNode = pActorNode->NextSiblingElement())
    {
        if (std::string(pActorNode->Name()) != "Actor")
        {
            LOG(Warning, "Invalid data. ActorList should contain Actor only");
            continue;
        }

        //Load the actor
        tinyxml2::XMLElement* pData = pActorNode->FirstChildElement("Data");
        FilePath dataFilePath = filePath;
        dataFilePath.ChangePath(pData->FirstChild()->Value());
        Actor* pNewActor = m_actorFactory.CreateActor(dataFilePath);
        if (!pNewActor)
            continue;
        pNewActor->SetWorld(m_pWorld);

        //Add the position of the actor in the map
        tinyxml2::XMLElement* pPositionNode = pActorNode->FirstChildElement("Position");
        int x = pPositionNode->IntAttribute("x");
        int y = pPositionNode->IntAttribute("y");
        TransformComponent* pTransformComponent = new TransformComponent(Point(x, y));

        pNewActor->AddComponent(pTransformComponent);

        //Push the new actor
        if (pNewActor)
            m_actorList.push_back(pNewActor);
        else
            LOG(Warning, "Failed to create an actor from %s", dataFilePath.GetFullPath().c_str());
    }

    return true;
}

void ActorManager::HandleKeyboardInput(const SDL_Keycode key)
{
    for (Actor* pActor : m_actorList)
    {
        pActor->HandleKeyboardInput(key);
    }
}

void ActorManager::OnNewTurnStarted()
{
    for (Actor* pActor : m_actorList)
    {
        pActor->OnNewTurnStarted();
    }
}

Actor* ActorManager::GetPlayerActor()
{
    for (Actor* pActor : m_actorList)
    {
        for (ActorComponent* pComponent : pActor->GetComponents())
        {
            if (pComponent->GetComponentId() == static_cast<int>(ActorComponent::Id::PlayerControllerComponent))
                return pActor;
        }
    }
    
    return nullptr;
}
