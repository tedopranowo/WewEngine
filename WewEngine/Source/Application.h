#pragma once

#include <FilePath.h>

struct SDL_Window;
struct SDL_Renderer;
class OpSys;
class Scene;
class IGameLogic;
class Renderer;

class Application
{
private:
    bool m_isQuitting;
    SDL_Window* m_pWindow;
    Renderer* m_pRenderer;
    OpSys* m_pOperatingSystem;

    float k_defaultScreenWidth;
    float k_defaultScreenHeight;

    const char* k_pDefaultWindowName = "Hello World!";
    IGameLogic* m_pGameLogic;

private:
    bool Initialize(const FilePath& filePath);
    void CleanUp();

public:
    Application();
    ~Application();

    void Run(const FilePath& filePath);
    void Quit() { m_isQuitting = true; }

    void ReceiveInput();
    void Update(float deltaTime);
    void Draw();
};