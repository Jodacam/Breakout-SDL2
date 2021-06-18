#include "SDLRender.h"
#include <iostream>

bool GameEngine::Renderer::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char *windowName)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Ha ocurrido un error" << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
    {
        std::cout << "Ha ocurrido un error" << IMG_GetError() << std::endl;
        SDL_Delay(3000);
        return false;
    }
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Ha ocurrido un error" << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return true;
}

bool GameEngine::Renderer::Close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return true;
}

bool GameEngine::Renderer::DrawBackground(Color color)
{
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderClear(renderer);
    return true;
}

bool GameEngine::Renderer::DrawScreen()
{

    SDL_RenderPresent(renderer);
    return true;
}

void GameEngine::Renderer::DrawImage(SDL_Texture *texture, int x,int y,int w,int h)
{

    SDL_Rect position;
    position.x = x;
    position.y = y;
    position.w = w;
    position.h = h;
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer, texture, NULL, &position);
}

SDL_Texture *GameEngine::Renderer::LoadTexture(const char *path)
{
    //Load a Surface and copy pixels
    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return text;
}

bool GameEngine::Renderer::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    
    return SDL_RenderClear(renderer);
}