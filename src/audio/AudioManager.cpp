#include "AudioManager.h"
#include "../consts/logger.h"
GameEngine::AudioManager *GameEngine::AudioManager::instance;

GameEngine::AudioManager *GameEngine::AudioManager::GetInstance()
{
    if (instance == NULL)
        instance = new GameEngine::AudioManager();
    return instance;
}

bool GameEngine::AudioManager::Init(int frequency, Uint16 format, int channels, int chunksize)
{

    if (instance == NULL)
        instance = new GameEngine::AudioManager();

    if (Mix_OpenAudio(frequency, format, channels, chunksize) == -1)
        return false;
    return true;
}

bool GameEngine::AudioManager::Close()
{
    Mix_CloseAudio();

    return true;
}

bool GameEngine::AudioManager::PlayMusic(const Song &song, bool loop)
{
    //printLog("Hello",LOG_TO_FILE);
    return Mix_PlayMusic(song.audio, loop ? -1 : 1) == 1;
}