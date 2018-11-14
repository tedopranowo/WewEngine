#pragma once

#include "../ActorComponent.h"
#include "../../Image/Image.h"

class SpriteRenderComponent :
    public ActorComponent
{
private:
    std::shared_ptr<Image> m_spriteImage;

public:
    SpriteRenderComponent();
    virtual ~SpriteRenderComponent();

    virtual void Draw(Renderer* pRenderer) override;
    virtual void Init(tinyxml2::XMLElement * pData, const FilePath& openedFilePath) override;

    virtual int GetComponentId() const override;
    virtual bool CopyData(const ActorComponent * pComponent) override;
};

