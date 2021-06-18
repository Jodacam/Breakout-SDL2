#ifndef _RENDER_H_
#define _RENDER_H_
#include <SDL.h>
#include <SDL_image.h>
namespace GameEngine
{
    struct Color {
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
        public:
            Renderer() {}
            bool Init(int SCREEN_WIDTH,int SCREEN_HEIGHT,const char* windowName);
            bool Close();
            bool DrawBackground(Color color);
            bool DrawScreen();
            void DrawImage(SDL_Texture *texture,int x = 0,int y = 0,int w = 0,int h = 0);
            bool ClearScreen();
            SDL_Texture* LoadTexture(const char* path);

    };

}
#endif