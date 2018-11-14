#pragma once

#include <FilePath.h>
#include <SDL_keycode.h>

class Renderer;

class IGameLogic
{
public:
    IGameLogic() {}
    virtual ~IGameLogic() {}

    virtual bool Load(const FilePath& filePath) = 0;

    virtual void HandleKeyboardInput(const SDL_Keycode key) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(Renderer* pRenderer) = 0;
};