#pragma once

struct SDL_Renderer;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void Draw(SDL_Renderer* pRenderer);
};

