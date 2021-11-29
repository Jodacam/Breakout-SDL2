#ifndef _RENDER_H_
#define _RENDER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Graphics.h"
#include "Text.h"
#include "../math/Vector.h"
namespace GameEngine
{
    struct Color
    {
        int red = 0;
        int green = 255;
        int blue = 255;
        int alpha = 255;
    };

    class Renderer
    {
    private:
        static Renderer* instance;
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        TTF_Font *font = NULL;
        int windowHeight = 0;
        int windowWidth = 0;
        int screenHeight = 0;
        int screenWidth = 0;
        float scaleH = 1.0f;
        float scaleW = 1.0f;

    public:
        Renderer() {}
        bool Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char *windowName);
        bool Close();
        bool DrawBackground(Color color);
        bool DrawScreen();
        /**
         * Draws and image or a SDL_Texture to the screen.
         * x and y is the position on the screen and w,h is the final size of the image.
         * By default stretch is used
        */
        void DrawImage(SDL_Texture *texture, float x, float y, float w, float h);
        void DrawImage(SDL_Texture *texture, float x = 0, float y = 0);
        void DrawImage(SDL_Texture *texture, const Vector position);
        void DrawImage(SDL_Texture *texture, const Vector position, const Vector size);
        void DrawImage(const Image *image, float x, float y);
        void DrawImage(const Image *image, float x, float y, float w, float h);
        void DrawImage(const Image *image, const Vector position);
        void DrawImage(const Image *image, const Vector position, const Vector size);
        /**
         * Draws a Sprite
        */
        void DrawSprite(Sprite *sprite, float x, float y, float w, float h);
        void DrawSprite(Sprite *sprite, float x, float y);
        void DrawSprite(Sprite *sprite, const Vector position);
        void DrawSprite(Sprite *sprite, const Vector position, const Vector size);

        /**
         * Draws Text
        */
       void DrawText(const StaticText& text);
       void DrawText(const StaticText& text, Vector position);
       void DrawText(const Text& text, Vector position);
        /**
         * Generates Text.
        */
        StaticText GenerateStaticText(std::string text);
        StaticText GenerateStaticText(std::string text, Vector size);
        SDL_Texture* GenerateTextTexture(std::string text);
        bool ClearScreen();
        void HandleWindowEvent(const SDL_Event *event);
        SDL_Renderer *GetInternalRender() { return renderer; }
        SDL_Texture *LoadTexture(const char *path);
        int ChangeRenderTarget(SDL_Texture *texture);

        
        static Renderer* GetInstance();
    };

}
#endif