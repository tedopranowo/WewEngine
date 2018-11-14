#include "PlayerControllerComponent.h"

#include <Logger.h>

#include "../Actor.h"
#include "../../Struct/Point.h"

PlayerControllerComponent::PlayerControllerComponent()
{
}

PlayerControllerComponent::~PlayerControllerComponent()
{
}

void PlayerControllerComponent::Init(tinyxml2::XMLElement * pData, const FilePath & openedFile)
{
    //NOTE: This component doesn't have any member variable
}

int PlayerControllerComponent::GetComponentId() const
{
    return static_cast<int>(ActorComponent::Id::PlayerControllerComponent);
}

bool PlayerControllerComponent::CopyData(const ActorComponent * pComponent)
{
    //NOTE: This component doesn't have a member variable, so owe don't need to do any dynamic cast
    //const PlayerControllerComponent* pPlayerControllerComponent = dynamic_cast<const PlayerControllerComponent*>(pComponent);

    ////Check if dynamic cast is success
    //if (!pPlayerControllerComponent)
    //{
    //    LOG(Warning, "Failed to copy script component");
    //    return false;
    //}
    return true;
}

void PlayerControllerComponent::HandleKeyboardInput(const SDL_Keycode key)
{
    Point moveDirection;

    switch (key)
    {
    case SDLK_w:    //UP
        LOG(Info, "W pressed");
        moveDirection.x = 0;
        moveDirection.y = -1;
        break;
    case SDLK_a:    //LEFT
        LOG(Info, "A pressed");
        moveDirection.x = -1;
        moveDirection.y = 0;
        break;
    case SDLK_s:    //DOWN
        LOG(Info, "S pressed");
        moveDirection.x = 0;
        moveDirection.y = 1;
        break;
    case SDLK_d:    //RIGHT
        LOG(Info, "D pressed");
        moveDirection.x = 1;
        moveDirection.y = 0;
        break;
    }

    if (m_pOwner->Move(moveDirection))
        //Only end turn if the movement is valida
        m_pOwner->EndTurn();
}
