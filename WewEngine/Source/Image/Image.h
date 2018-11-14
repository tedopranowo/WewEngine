#pragma once

#include <string>

#include <FilePath.h>

#include "../Struct/Point.h"
#include "../Struct/Rect.h"

#include "../Tools/ResourceCache.h"

struct SDL_Texture;
struct SDL_Renderer;

class Image : public ICachable<Image>
{
    friend class ResourceCache<Image>;

private:
    FilePath m_filePath;
	Point m_resolution;
	SDL_Texture* m_pImageTexture;

public:
    Image();
	Image(const Image& copy);
	~Image();

	SDL_Texture* GetTexture(SDL_Renderer* pRen);
	Rect GetRect() const;

private:
	void DestroyTexture();
    bool MeasureImageResolution();

    virtual bool Load(const FilePath & filePath) override;
};

