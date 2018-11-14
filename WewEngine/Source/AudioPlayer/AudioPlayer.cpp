#include "AudioPlayer.h"

#include <Logger.h>

AudioPlayer AudioPlayer::m_sAudioPlayer;

void AudioPlayer::Init()
{
	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
	{
        LOG(Warning, "Mix_Init error");
        LOG(Todo, "Fix Mix_Init error");
	}

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
}

void AudioPlayer::PlayBGM(const std::string& filePath)
{
	m_sAudioPlayer.m_pBGMMusic = Mix_LoadMUS(filePath.c_str());
    if (Mix_PlayMusic(m_sAudioPlayer.m_pBGMMusic, -1) == -1)
        LOG(Warning, "PlayBGM failed: %s", Mix_GetError());
}

void AudioPlayer::PlaySoundEffect(const std::string& filePath)
{
	m_sAudioPlayer.m_pSoundEffect = Mix_LoadWAV(filePath.c_str());
	Mix_PlayChannel(-1, m_sAudioPlayer.m_pSoundEffect, 0);
}   

AudioPlayer::AudioPlayer()
{
	Init();
}

AudioPlayer::~AudioPlayer()
{
	Mix_FreeMusic(m_pBGMMusic);
	Mix_FreeChunk(m_pSoundEffect);
	Mix_CloseAudio();
	Mix_Quit();
}

void AudioPlayer::StopBGM()
{
	if (m_sAudioPlayer.m_pBGMMusic)
		Mix_FreeMusic(m_sAudioPlayer.m_pBGMMusic);
}

void AudioPlayer::StopSoundEffect()
{
	if (m_sAudioPlayer.m_pSoundEffect)
		Mix_FreeChunk(m_sAudioPlayer.m_pSoundEffect);
}

