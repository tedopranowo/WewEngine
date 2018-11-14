#include "Image.h"

#include <SDL_image.h>
#include <SDL.h>

#include <Logger.h>

Image::Image()
    : m_pImageTexture{ nullptr }
{
}

Image::Image(const Image & copy)
	: m_filePath{ copy.m_filePath }
	, m_resolution{ copy.m_resolution }
	, m_pImageTexture{ nullptr }
{
}

Image::~Image()
{
	DestroyTexture();
}

SDL_Texture* Image::GetTexture(SDL_Renderer* pRen)
{
	if (!m_pImageTexture)	//if texture hasn't been created
	{
        //Create the texture 
        m_pImageTexture = IMG_LoadTexture(pRen, m_filePath.GetFullPath().c_str());

        if (!m_pImageTexture)
        {
            LOG(Warning, IMG_GetError());
            return nullptr;
        }
	}
	return m_pImageTexture;
}

Rect Image::GetRect() const
{
    return Rect{ 0, 0, m_resolution.x, m_resolution.y };
}

void Image::DestroyTexture()
{
	if (m_pImageTexture)
	{
		SDL_DestroyTexture(m_pImageTexture);
		m_pImageTexture = nullptr;
	}
}

bool Image::MeasureImageResolution()
{
    //Open the file as a surface
    SDL_Surface* pSurface = IMG_Load(m_filePath.GetFullPath().c_str());

    //If failed to create the surface
    if (!pSurface)
    {
        LOG(Warning, IMG_GetError());
        return false;
    }

    //Save the width and height
    m_resolution.x = pSurface->w;
    m_resolution.y = pSurface->h;

    //Clean up
    SDL_FreeSurface(pSurface);

    return true;
}

bool Image::Load(const FilePath & filePath)
{
    DestroyTexture();
    m_filePath = filePath;
    return MeasureImageResolution();
}