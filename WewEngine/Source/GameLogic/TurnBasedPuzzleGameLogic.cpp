#include "TurnBasedPuzzleGameLogic.h"

#include "..\World\World.h"

TurnBasedPuzzleGameLogic::TurnBasedPuzzleGameLogic()
{
}


TurnBasedPuzzleGameLogic::~TurnBasedPuzzleGameLogic()
{
    CleanUp();
}

void TurnBasedPuzzleGameLogic::Init(Renderer * pRenderer)
{
    m_camera.Init(pRenderer);
}

bool TurnBasedPuzzleGameLogic::Load(const FilePath & filePath)
{
    if (m_pWorld == nullptr)
        m_pWorld = new World(this);

    //Load the file
    if (!m_pWorld->Load(filePath))
        return false;

    return true;
}

void TurnBasedPuzzleGameLogic::EndTurn()
{
    m_pWorld->OnNewTurnStarted();
}

void TurnBasedPuzzleGameLogic::Update(float deltaTime)
{
    //Set the camera position
    Rect playerRect = m_pWorld->GetPlayerActor()->GetRect();

    m_camera.SetPosition(Point(playerRect.x - 462, playerRect.y - 334));
}

void TurnBasedPuzzleGameLogic::Draw(Renderer* pRenderer)
{
    m_pWorld->Draw(pRenderer);
}

void TurnBasedPuzzleGameLogic::CleanUp()
{
    if (m_pWorld != nullptr)
    {
        delete m_pWorld;
        m_pWorld = nullptr;
    }
}

void TurnBasedPuzzleGameLogic::HandleKeyboardInput(const SDL_Keycode key)
{
    m_pWorld->HandleKeyboardInput(key);
}
