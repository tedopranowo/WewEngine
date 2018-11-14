#pragma once

#include "IGameLogic.h"
#include "FilePath.h"
#include "../Camera/Camera.h"

class World;
class Renderer;

class TurnBasedPuzzleGameLogic :
    public IGameLogic
{
private:
    World* m_pWorld;
    Camera m_camera;

public:
    //Initialization
    TurnBasedPuzzleGameLogic();
    virtual ~TurnBasedPuzzleGameLogic();

    void Init(Renderer* pRenderer);
    virtual bool Load(const FilePath& filePath) override;

    //Game logic
    void EndTurn();

    // Inherited via IGameLogic
    virtual void Update(float deltaTime) override;
    virtual void Draw(Renderer* pRenderer) override;
    virtual void HandleKeyboardInput(const SDL_Keycode key) override;
    
    void CleanUp();
};