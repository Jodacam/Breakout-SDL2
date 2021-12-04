#ifndef GAME_ENGINE_TEXT_H
#define GAME_ENGINE_TEXT_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../math/Vector.h"
namespace GameEngine
{
    /**
     * Container struct for static text.
     * It can't change its text.
    */
    struct StaticText
    {
        /* data */
        SDL_Texture *textureData = NULL;
        std::string text;
        Vector size;
        ~StaticText();
    };

    /**
     * Container struct for static text.
     * Change the text can be expensive.
    */
    class Text
    {
    private:
        /* data */
        std::string text;
    public:
        /* data */
        SDL_Texture *textureData = NULL;
        Vector size;

        inline std::string GetText() {return text;}
        /**
         * Changes the inner text. It can be a expensive operation to do each frame.
        */
        void SetText(std::string text,bool resize = false);
        Text() {}
        Text(std::string t);
        Text(std::string t, Vector s);
        ~Text();
    };

}

#endif //GAME_ENGINE_TEXT_H