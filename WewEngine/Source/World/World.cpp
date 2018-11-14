#include "World.h"

#include <Logger.h>
#include <SDL_render.h>

#include "../Struct/Rect.h"
#include "../WDataLoader/WDataLoader.h"
#include "../AudioPlayer/AudioPlayer.h"

World::World(TurnBasedPuzzleGameLogic* pGameLogic)
    : m_actorManager(this)
    , m_tileSize(100, 100)
    , m_pGameLogic(pGameLogic)
{
}

World::~World()
{
}

void World::Draw(Renderer* pRenderer)
{
    m_map.Draw(pRenderer);
    m_actorManager.Draw(pRenderer);
}

bool World::Load(const FilePath & filePath)
{
    WDataLoader fileLoader(filePath);
    fileLoader.Load();

    //Check if the object type is correct
    if (fileLoader.GetObjectType() != "World")
    {
        LOG(Error, "Invalid object type at file ", fileLoader.GetFilePath().GetFileName());
        return false;
    }

    //Load the map
    FilePath mapFilePath = filePath;
    mapFilePath.ChangePath(fileLoader["Map"]);
    if (!m_map.Load(mapFilePath))
        return false;

    //Load all the actors
    FilePath actorListFilePath = filePath;
    actorListFilePath.ChangePath(fileLoader["ActorList"]);
    if (!m_actorManager.Load(actorListFilePath))
        return false;

    //Play BGM
    FilePath bgmFilePath = filePath;
    bgmFilePath.ChangePath(fileLoader["BGM"]);
    AudioPlayer::PlayBGM(bgmFilePath.GetFullPath());

    return true;
}

void World::HandleKeyboardInput(const SDL_Keycode key)
{
    m_actorManager.HandleKeyboardInput(key);
}

void World::OnNewTurnStarted()
{
    m_actorManager.OnNewTurnStarted();
}
