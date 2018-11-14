#pragma once

#include "Renderer.h"

struct SDL_Window;
struct SDL_Renderer;

class RendererSDL :
    public Renderer
{
private:
    SDL_Renderer* m_pRenderer;
    SDL_Window* m_pWindow;

public:
    RendererSDL(SDL_Window* pWindow);
    virtual ~RendererSDL();

    // Inherited via Renderer
    virtual bool Init() override;
    virtual void RenderImage(Image * pImage, const Rect& worldRectTransform) override;
    virtual void DrawToScreen() override;
    virtual void ClearScreen() override;
};

