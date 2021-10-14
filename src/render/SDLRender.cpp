#include "SDLRender.h"
#include <iostream>

bool GameEngine::Renderer::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char *windowName)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
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
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        std::cout << "Ha ocurrido un error" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    screenHeight = SCREEN_HEIGHT;
    screenWidth = SCREEN_WIDTH;
    std::cout << "Anchura en size: " << windowWidth << " Altura en size: " << windowHeight << std::endl;
    scaleH = (float)windowHeight / (float)screenHeight;
    scaleW = (float)windowWidth / (float)screenWidth;
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return true;
}

bool GameEngine::Renderer::Close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
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

void GameEngine::Renderer::DrawImage(SDL_Texture *texture, int x, int y, int w, int h)
{

    SDL_Rect position;
    position.x = x * scaleW;
    position.y = y * scaleH;
    position.w = w * scaleW;
    position.h = h * scaleH;
    SDL_RenderCopy(this->renderer, texture, NULL, &position);
}

void GameEngine::Renderer::DrawImage(SDL_Texture *texture, int x, int y)
{

    SDL_Rect position;
    position.x = x * scaleW;
    position.y = y * scaleH;
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    position.h = position.h * scaleH;
    position.w = position.w * scaleW;
    SDL_RenderCopy(this->renderer, texture, NULL, &position);
}

SDL_Texture *GameEngine::Renderer::LoadTexture(const char *path)
{
    // Load a Surface and copy pixels
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

void GameEngine::Renderer::HandleWindowEvent(const SDL_Event *event)
{
    switch (event->window.event)
    {
    case SDL_WINDOWEVENT_SHOWN:
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        break;
    case SDL_WINDOWEVENT_EXPOSED:
        break;
    case SDL_WINDOWEVENT_MOVED:
        break;
    case SDL_WINDOWEVENT_RESIZED:
        SDL_Log("Window %d resized to %dx%d",
                event->window.windowID, event->window.data1,
                event->window.data2);
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        scaleH = (float)windowHeight / (float)screenHeight;
        scaleW = (float)windowWidth / (float)screenWidth;
        break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        SDL_Log("Window %d size changed to %dx%d",
                event->window.windowID, event->window.data1,
                event->window.data2);
        break;
    case SDL_WINDOWEVENT_MINIMIZED:
        SDL_Log("Window %d minimized", event->window.windowID);
        break;
    case SDL_WINDOWEVENT_MAXIMIZED:
        SDL_Log("Window %d maximized", event->window.windowID);
        break;
    case SDL_WINDOWEVENT_RESTORED:
        break;
    case SDL_WINDOWEVENT_ENTER:
        break;
    case SDL_WINDOWEVENT_LEAVE:
        break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
        break;
    case SDL_WINDOWEVENT_CLOSE:
        SDL_Log("Window %d closed", event->window.windowID);
        break;
    default:
        SDL_Log("Window %d got unknown event %d",
                event->window.windowID, event->window.event);
        break;
    }
}
