#include "RendererSDL.h"

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <Logger.h>

#include "../Image/Image.h"

RendererSDL::RendererSDL(SDL_Window * pWindow)
    : m_pWindow(pWindow)
{
}

RendererSDL::~RendererSDL()
{
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(m_pRenderer);
}

bool RendererSDL::Init()
{
    m_pRenderer = SDL_CreateRenderer(m_pWindow, 0, 0);
    if (!m_pRenderer)
    {
        LOG(Error, SDL_GetError());
        return false;
    }

    //Initialize Font and image
    if (TTF_Init() != 0)
    {
        LOG(Error, "TTF_Init error");
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        LOG(Error, "IMG_Init error");
        return false;
    }

    return true;
}

void RendererSDL::RenderImage(Image * pImage, const Rect & worldRectTransform)
{
    if (pImage)
    {
        //transform from world rect to camera rect
        Rect renderTarget = worldRectTransform;
        renderTarget.x -= m_renderViewPosition.x;
        renderTarget.y -= m_renderViewPosition.y;

        SDL_RenderCopy(m_pRenderer, pImage->GetTexture(m_pRenderer), &pImage->GetRect(), &renderTarget);
    }
}

void RendererSDL::DrawToScreen()
{
    //Draw
    SDL_RenderPresent(m_pRenderer);
}

void RendererSDL::ClearScreen()
{
    //Clear Screen
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);
}
