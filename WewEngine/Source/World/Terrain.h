#pragma once

#include <memory>
#include <vector>

#include "../Image/Image.h"
#include "../Actor/Actor.h"
#include "../Tools/ResourceCache.h"

class Renderer;
class GameObject;

class Terrain : ICachable<Terrain>
{
    friend class ResourceCache<Terrain>;

private:
    std::shared_ptr<Image> m_pImage;
    std::vector<Actor::Tag> m_preventedUnitTagList;

public:
    Terrain() {}
    Terrain(const FilePath& filePath);
    ~Terrain() {}

    void Draw(Renderer* pRenderer, const Rect& drawRect);
    bool IsTravelable(Actor* pUnit);

private:
    virtual bool Load(const FilePath& filePath) override;
};

