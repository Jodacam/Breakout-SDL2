#ifndef GAME_ENGINE_AUDIO_H_
#define GAME_ENGINE_AUDIO_H_
#include <SDL2/SDL_mixer.h>
namespace LightCanvas
{
    /**
    * Define structs to store music or sound effects.
    */

    struct Song
    {
        Mix_Music *audio;
        int duration;
        Song() {};
        Song(Mix_Music *s) : audio(s) {};
        ~Song()
        {
            if(audio != NULL)
                Mix_FreeMusic(audio);
        };
    };

    struct SoundEffect
    {
        Mix_Chunk *audio;
        int duration;
        SoundEffect() {};
        SoundEffect(Mix_Chunk *s) : audio(s) {};
        ~SoundEffect()
        {
            if(audio != NULL)
                Mix_FreeChunk(audio);
        }
    };

}

#endif // GAME_ENGINE_AUDIO_H_