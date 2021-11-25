#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_
#include <SDL2/SDL_mixer.h>
#include "Audio.h"
namespace GameEngine
{
    class AudioManager
    {
    private:
        static AudioManager *instance;
        AudioManager() {}

    public:
        static AudioManager *GetInstance();
        static bool Init(int frequency, Uint16 format, int channels, int chunksize);
        bool Close();
        bool PlayMusic(const Song &song, bool loop);
    };
}

#endif //AUDIO_MANAGER_H_