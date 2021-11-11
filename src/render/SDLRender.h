#ifndef _RENDER_H_
#define _RENDER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../math/Vector.h"
namespace GameEngine
{
    struct Color
    {
        int red = 0;
        int green = 0;
        int blue = 255;
        int alpha = 255;
    };

    class Renderer
    {
    private:
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
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
        void DrawImage(SDL_Texture *texture, float x, float y, float w, float h);
        void DrawImage(SDL_Texture *texture, int x = 0, int y = 0);
        void DrawImage(SDL_Texture *texture, const Vector position);
        void DrawImage(SDL_Texture *texture, const Vector position, const Vector size);
        bool ClearScreen();
        void HandleWindowEvent(const SDL_Event *event);
        SDL_Renderer *getInternalRender() { return renderer; }
        SDL_Texture *LoadTexture(const char *path);
    };

}
#endif