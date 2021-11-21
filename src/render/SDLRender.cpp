#include "SDLRender.h"
#include "../consts/logger.h"
#include <iostream>

GameEngine::Renderer *GameEngine::Renderer::instance;
GameEngine::Renderer *GameEngine::Renderer::GetInstance()
{

    if (!GameEngine::Renderer::instance)
    {
        GameEngine::Renderer::instance = new GameEngine::Renderer();
    }

    return GameEngine::Renderer::instance;
}


bool GameEngine::Renderer::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char *windowName)
{
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0)
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

    if (TTF_Init() < 0)
    {
        printLog(TTF_GetError());
        return false;
    }

#ifndef PSP
    Uint32 SDL_Flag = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
#endif
#ifdef PSP
    Uint32 SDL_Flag = SDL_WINDOW_MAXIMIZED;
#endif
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_Flag);
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
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    font = TTF_OpenFont("resources/font/FSEX300.ttf", 16);

    return true;
}

bool GameEngine::Renderer::Close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
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

GameEngine::StaticText GameEngine::Renderer::GenerateStaticText(std::string text)
{
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    //Vector a;
    int x, y;
    SDL_QueryTexture(texture, NULL, NULL, &x, &y);

    StaticText staticText {textureData : texture,text:text, size : Vector(x, y)};

    SDL_FreeSurface(surface);

    return staticText;
}

GameEngine::StaticText GameEngine::Renderer::GenerateStaticText(std::string text, Vector size)
{
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    //Vector a;

    StaticText staticText{textureData : texture, size : size};

    SDL_FreeSurface(surface);

    return staticText;
}

SDL_Texture* GameEngine::Renderer::GenerateTextTexture(std::string text) {
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void GameEngine::Renderer::DrawImage(SDL_Texture *texture, float x, float y, float w, float h)
{
    SDL_FRect position;
    position.x = x * scaleW;
    position.y = y * scaleH;
    position.w = w * scaleW;
    position.h = h * scaleH;
    SDL_RenderCopyF(this->renderer, texture, NULL, &position);
}
void GameEngine::Renderer::DrawImage(SDL_Texture *texture, float x, float y)
{
    SDL_FRect position;
    position.x = x * scaleW;
    position.y = y * scaleH;
    int h = 0;
    int w = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    position.h = h * scaleH;
    position.w = w * scaleW;
    SDL_RenderCopyF(this->renderer, texture, NULL, &position);
}
void GameEngine::Renderer::DrawImage(SDL_Texture *texture, const Vector position)
{
    DrawImage(texture, position.x, position.y);
}
void GameEngine::Renderer::DrawImage(SDL_Texture *texture, const Vector position, const Vector size)
{
    DrawImage(texture, position.x, position.y, size.x, size.y);
}

void GameEngine::Renderer::DrawImage(const Image *image, const Vector position)
{
    DrawImage(image, position.x, position.y, image->width, image->height);
}

void GameEngine::Renderer::DrawImage(const Image *image, const Vector position, const Vector size)
{
    DrawImage(image, position.x, position.y, size.x, size.y);
}
void GameEngine::Renderer::DrawImage(const Image *image, float x, float y)
{
    DrawImage(image->texture, x, y, image->width, image->height);
}
void GameEngine::Renderer::DrawImage(const Image *image, float x, float y, float w, float h)
{
    DrawImage(image->texture, x, y, w, h);
}

void GameEngine::Renderer::DrawSprite(Sprite *sprite, float x, float y, float w, float h)
{
    /**
     * TODO
     * - Offset Sprite. If using the same Texture offset the sprite coordinates.
    */
    SDL_Rect srcrect = {x : sprite->width * sprite->x, y : sprite->width * sprite->y, w : sprite->width, h : sprite->height};
    SDL_FRect dstrect = {x : x * scaleW, y : y * scaleH, w : w * scaleW, h : h * scaleW};
    SDL_RenderCopyF(this->renderer, sprite->source->texture, &srcrect, &dstrect);
}

void GameEngine::Renderer::DrawSprite(Sprite *sprite, float x, float y)
{
    DrawSprite(sprite, x, y, sprite->width, sprite->height);
}

void GameEngine::Renderer::DrawSprite(Sprite *sprite, const Vector position)
{
    DrawSprite(sprite, position.x, position.y, sprite->width, sprite->height);
}

void GameEngine::Renderer::DrawSprite(Sprite *sprite, const Vector position, const Vector size)
{
    DrawSprite(sprite, position.x, position.y, size.x, size.y);
}

void GameEngine::Renderer::DrawText(const StaticText &text, Vector position)
{
    SDL_FRect dstRect;
    dstRect.x = position.x * scaleW;
    dstRect.y = position.y * scaleH;
    dstRect.w = text.size.x * scaleW;
    dstRect.h = text.size.y * scaleH;
    SDL_RenderCopyF(this->renderer, text.textureData, NULL, &dstRect);
}
void GameEngine::Renderer::DrawText(const Text &text, Vector position)
{
    SDL_FRect dstRect;
    dstRect.x = position.x * scaleW;
    dstRect.y = position.y * scaleH;
    dstRect.w = text.size.x * scaleW;
    dstRect.h = text.size.y * scaleH;
    SDL_RenderCopyF(this->renderer, text.textureData, NULL, &dstRect);
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
