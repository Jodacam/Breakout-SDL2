#include "AudioManager.h"
#include "../resourceManager/AssetsManager.h"
#include "../consts/logger.h"
LightCanvas::AudioManager *LightCanvas::AudioManager::instance;

LightCanvas::AudioManager *LightCanvas::AudioManager::GetInstance()
{
    if (instance == NULL)
        instance = new LightCanvas::AudioManager();
    return instance;
}

bool LightCanvas::AudioManager::Init(int frequency, Uint16 format, int channels, int chunksize)
{

    if (instance == NULL)
        instance = new LightCanvas::AudioManager();

    if (Mix_OpenAudio(frequency, format, channels, chunksize) == -1)
        return false;

    //Mix_Init(MIX_INIT_OGG);

    //Allocate chanels on memory for sound effects.
    Mix_AllocateChannels(8);

    return true;
}

bool LightCanvas::AudioManager::Close()
{
    Mix_CloseAudio();

    return true;
}

bool LightCanvas::AudioManager::PlayMusic(const Song &song, bool loop)
{
    return Mix_PlayMusic(song.audio, loop ? -1 : 1) == 1;
}

bool LightCanvas::AudioManager::PlayMusic(std::string asset, bool loop)
{
    return PlayMusic(*(AssetManager::GetInstance()->GetSong(asset).get()), loop);
}

bool LightCanvas::AudioManager::PauseMusic()
{
    Mix_PauseMusic();
    return true;
}

int LightCanvas::AudioManager::PlaySoundEffect(std::string asset, bool loop)
{
    return PlaySoundEffect(*(AssetManager::GetInstance()->GetSoundEffect(asset).get()), loop);
}
int LightCanvas::AudioManager::PlaySoundEffect(const SoundEffect &effect, bool loop)
{

    return Mix_PlayChannel(-1, effect.audio, loop ? -1 : 0);
}
