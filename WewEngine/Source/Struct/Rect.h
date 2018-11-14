#pragma once

#include "SDL_rect.h"

struct Rect :
    public SDL_Rect
{
public:
    Rect(int x, int y, int w, int h) : SDL_Rect{ x, y, w, h } {}
    Rect(const Rect& rect) : SDL_Rect{ rect.x, rect.y, rect.w, rect.h } {}	//copy constructor
};

