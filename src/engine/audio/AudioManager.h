#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_
#include <SDL2/SDL_mixer.h>
#include "Audio.h"
#include <string>
namespace LightCanvas
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
        /**
         * Plays a song at the background.
        */
        bool PlayMusic(const Song &song, bool loop = true);
        bool PlayMusic(std::string asset, bool loop = true);

        bool PauseMusic();
        /**
         * Plays a sound effect.
         * Returns the channel used for the effect. Becuase the effect has a duration,
         * the int could change and point to another sound effect.
         * 
        */
        int PlaySoundEffect(std::string asset, bool loop = false);
        int PlaySoundEffect(const SoundEffect &effect, bool loop = false);
    };
}

#endif //AUDIO_MANAGER_H_