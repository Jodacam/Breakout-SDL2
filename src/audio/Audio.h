#ifndef GAME_ENGINE_AUDIO_H_
#define GAME_ENGINE_AUDIO_H_
#include <SDL2/SDL_mixer.h>
namespace GameEngine
{
    /**
    * Define structs to store music or sound effects.
    */

    struct Song
    {
        Mix_Music *audio;
        int duration;
        
    };

    struct SoundEffect
    {
        Mix_Chunk *audio;
        int duration;
    };

}

#endif // GAME_ENGINE_AUDIO_H_