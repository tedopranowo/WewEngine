#include "SpriteRenderComponent.h"

#include <tinyxml2.h>

#include "../Actor.h"
#include "../ActorFactory.h"

#include "../../Renderer/Renderer.h"

SpriteRenderComponent::SpriteRenderComponent()
{
}


SpriteRenderComponent::~SpriteRenderComponent()
{
}

void SpriteRenderComponent::Draw(Renderer * pRenderer)
{
    pRenderer->RenderImage(m_spriteImage.get(), m_pOwner->GetRect());
}

void SpriteRenderComponent::Init(tinyxml2::XMLElement * pData, const FilePath& openedFilePath)
{
    for (auto pNode = pData->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
    {
        if (std::string(pNode->Name()) == "Image")
        {
            FilePath imageFilePath = openedFilePath;
            imageFilePath.ChangePath(pNode->FirstChild()->Value());
            m_spriteImage = ResourceCache<Image>::Get(imageFilePath);
        }
    }
}

int SpriteRenderComponent::GetComponentId() const
{
    return static_cast<int>(Id::SpriteRenderComponent);
}

bool SpriteRenderComponent::CopyData(const ActorComponent * pComponent)
{
    const SpriteRenderComponent* pConvertedComponent = dynamic_cast<const SpriteRenderComponent*>(pComponent);

    //If conversion failed, return false
    if (!pConvertedComponent)
        return false;

    //If conversion success, copy the data
    m_spriteImage = pConvertedComponent->m_spriteImage;

    return true;
}
