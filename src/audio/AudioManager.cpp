#include "AudioManager.h"
#include "../resourceManager/AssetsManager.h"
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

    //Mix_Init(MIX_INIT_OGG);

    //Allocate chanels on memory for sound effects.
    Mix_AllocateChannels(8);

    return true;
}

bool GameEngine::AudioManager::Close()
{
    Mix_CloseAudio();

    return true;
}

bool GameEngine::AudioManager::PlayMusic(const Song &song, bool loop)
{
    return Mix_PlayMusic(song.audio, loop ? -1 : 1) == 1;
}
int GameEngine::AudioManager::PlaySoundEffect(std::string asset, bool loop) {
    return PlaySoundEffect(*(AssetManager::GetInstance()->GetSoundEffect(asset).get()));
}
int GameEngine::AudioManager::PlaySoundEffect(const SoundEffect &effect, bool loop)
{

    return Mix_PlayChannel(-1, effect.audio, loop ? -1 : 0);
}
