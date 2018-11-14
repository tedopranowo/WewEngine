#include "Application.h"

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Logger.h"
#include "WewEngineStd.h"

#include "Renderer\RendererSDL.h"
#include "Timer.h"
#include "..\..\OS\Source\OpSys.h"
#include "GameLogic\TurnBasedPuzzleGameLogic.h"
#include "AudioPlayer\AudioPlayer.h"

bool Application::Initialize(const FilePath& filePath)
{
    //Operating System
    m_pOperatingSystem = OpSys::Create();
    m_pOperatingSystem->CheckFreeDiskSpace(1024 << 20);

    if (m_pOperatingSystem->WindowAlreadyExists("Hello World!"))
        return false;

    //SDL
    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        LOG(Error, "SDL Initialization error");
        return false;
    }

    // Opening a window
    m_pWindow = SDL_CreateWindow("Hello World!", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
    if (!m_pWindow)
    {
        LOG(Error, "SDL_CreateWindow error");
        return false;
    }

    //Initialize Renderer
    m_pRenderer = new RendererSDL(m_pWindow);
    if (!m_pRenderer->Init())
    {
        LOG(Error, "Failed to initialize Renderer");
        return false;
    }

    //Initialize Audio
    //if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
    //{
    //    LOG(Warning, "Mix_Init error");
    //    LOG(Todo, "Fix Mix_Init error");
    //    //return false;
    //}

    //Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    //Init game logic
    TurnBasedPuzzleGameLogic* pGameLogic = new TurnBasedPuzzleGameLogic();
    pGameLogic->Init(m_pRenderer);
    m_pGameLogic = pGameLogic;
    if (!m_pGameLogic->Load(filePath))
        return false;

    LOG(Info, "Initialization success");

    return true;
}

void Application::CleanUp()
{
    if (m_pGameLogic)
    {
        delete m_pGameLogic;
        m_pGameLogic = nullptr;
    }
    Mix_CloseAudio();
    Mix_Quit();
    
    //Close renderer
    delete m_pRenderer;
    m_pRenderer = nullptr;

    if (m_pWindow)
    {
        SDL_DestroyWindow(m_pWindow);	        //Destroy win
        m_pWindow = nullptr;
    }
    SDL_Quit();									//quit SDL

    //Clean operating system
    delete m_pOperatingSystem;
    m_pOperatingSystem = nullptr;
}

Application::Application()
    : m_isQuitting(false)
{
}


Application::~Application()
{
    CleanUp();
}

void Application::Run(const FilePath& filePath)
{
    if (!Initialize(filePath))
    {
        CleanUp();
        return;
    }

    Timer timer;
    float deltaTime = 0;

    while (!m_isQuitting)
    {
        timer.Start();

        ReceiveInput();
        Update(deltaTime);
        Draw();
        AudioPlayer::Loop();

        deltaTime = timer.GetDeltaTime();
    }
}

void Application::ReceiveInput()
{
    SDL_Event e;
    //loop as long as an event still available and the state isn't null
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            m_isQuitting = true;
            break;
        case SDL_KEYDOWN:
            m_pGameLogic->HandleKeyboardInput(e.key.keysym.sym);
            break;
        //case SDL_MOUSEBUTTONUP:
        //    switch (e.button.button)
        //    {
        //    case SDL_BUTTON_LEFT:
        //        m_pState->HandleMouseLeftClick();
        //        break;
        //    case SDL_BUTTON_RIGHT:
        //        m_pState->HandleMouseRightClick();
        //        break;
        //    }
        //    break;
        //case SDL_MOUSEMOTION:
        //    m_pState->HandleMouseMovement(e.motion.x, e.motion.y);
        }
    }

    LOG(Todo, "finish ReceiveInput()");
}

void Application::Update(float deltaTime)
{
    m_pGameLogic->Update(deltaTime);
}

void Application::Draw()
{
    m_pRenderer->ClearScreen();

    m_pGameLogic->Draw(m_pRenderer);

    m_pRenderer->DrawToScreen();
}
