#pragma once

#include <string>
#include <SDL_mixer.h>

class AudioPlayer
{
private:
	static AudioPlayer m_sAudioPlayer;
	Mix_Music* m_pBGMMusic;
	Mix_Chunk* m_pSoundEffect;

public:
	static void PlayBGM(const std::string& filePath);
	static void PlaySoundEffect(const std::string& filePath);

    static void Loop() { if (Mix_PlayingMusic() == 0) Mix_RewindMusic(); }

private:
	AudioPlayer();
	~AudioPlayer();

	static void StopBGM();
	static void StopSoundEffect();

	void Init();
};

