#include "SDLRender.h"
#include "../consts/logger.h"
#include <iostream>

LightCanvas::Renderer* LightCanvas::Renderer::instance;
LightCanvas::Renderer* LightCanvas::Renderer::GetInstance()
{

    if (!LightCanvas::Renderer::instance)
    {
        LightCanvas::Renderer::instance = new LightCanvas::Renderer();
    }

    return LightCanvas::Renderer::instance;
}

bool LightCanvas::Renderer::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* windowName)
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
    scaleH = 1;
    scaleW = 1;
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    font = TTF_OpenFont("resources/font/KenneyPixelSquare.ttf", 16);

    return true;
}

bool LightCanvas::Renderer::Close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return true;
}

bool LightCanvas::Renderer::DrawBackground(Color color)
{
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderClear(renderer);
    return true;
}

bool LightCanvas::Renderer::DrawScreen()
{

    SDL_RenderPresent(renderer);
    return true;
}

LightCanvas::StaticText LightCanvas::Renderer::GenerateStaticText(std::string text)
{
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, 480);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // Vector a;
    int x, y;
    SDL_QueryTexture(texture, NULL, NULL, &x, &y);

    StaticText staticText{ textureData: texture, text : text, size : Vector(x, y) };

    SDL_FreeSurface(surface);

    return staticText;
}

LightCanvas::StaticText LightCanvas::Renderer::GenerateStaticText(std::string text, Vector size)
{
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // Vector a;

    StaticText staticText{ textureData: texture, size : size };

    SDL_FreeSurface(surface);

    return staticText;
}

SDL_Texture* LightCanvas::Renderer::GenerateTextTexture(std::string text)
{
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, 480);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
void LightCanvas::Renderer::DrawFillScreen(SDL_Texture* texture) {
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = this->screenWidth;
    dstRect.h = this->screenHeight;
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

}
void LightCanvas::Renderer::DrawImage(SDL_Texture* texture, float x, float y, float w, float h)
{
    SDL_FRect position;
    position.x = x * scaleW;
    position.y = y * scaleH;
    position.w = w * scaleW;
    position.h = h * scaleH;
    SDL_RenderCopyF(this->renderer, texture, NULL, &position);
}
void LightCanvas::Renderer::DrawImage(SDL_Texture* texture, float x, float y)
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
void LightCanvas::Renderer::DrawImage(SDL_Texture* texture, const Vector position)
{
    DrawImage(texture, position.x, position.y);
}
void LightCanvas::Renderer::DrawImage(SDL_Texture* texture, const Vector position, const Vector size)
{
    DrawImage(texture, position.x, position.y, size.x, size.y);
}

void LightCanvas::Renderer::DrawImage(const Image* image, const Vector position)
{
    DrawImage(image, position.x, position.y, image->width, image->height);
}

void LightCanvas::Renderer::DrawImage(const Image* image, const Vector position, const Vector size)
{
    DrawImage(image, position.x, position.y, size.x, size.y);
}
void LightCanvas::Renderer::DrawImage(const Image* image, float x, float y)
{
    DrawImage(image->texture, x, y, image->width, image->height);
}
void LightCanvas::Renderer::DrawImage(const Image* image, float x, float y, float w, float h)
{
    DrawImage(image->texture, x, y, w, h);
}

void LightCanvas::Renderer::DrawSprite(Sprite* sprite, float x, float y, float w, float h)
{
    /**
     * TODO
     * - Offset Sprite. If using the same Texture offset the sprite coordinates.
     */
    SDL_Rect srcrect = { x: sprite->width * sprite->x, y : sprite->width * sprite->y, w : sprite->width, h : sprite->height };
    SDL_FRect dstrect = { x: x * scaleW, y : y * scaleH, w : w * scaleW, h : h * scaleW };
    SDL_RenderCopyF(this->renderer, sprite->source->texture, &srcrect, &dstrect);
}


void LightCanvas::Renderer::DrawSprite(Sprite* sprite, float x, float y)
{
    DrawSprite(sprite, x, y, sprite->width, sprite->height);
}

void LightCanvas::Renderer::DrawSprite(Sprite* sprite, const Vector position)
{
    DrawSprite(sprite, position.x, position.y, sprite->width, sprite->height);
}

void LightCanvas::Renderer::DrawSprite(Sprite* sprite, const Vector position, const Vector size)
{
    DrawSprite(sprite, position.x, position.y, size.x, size.y);
}

void LightCanvas::Renderer::DrawSprite(Sprite sprite, float x, float y, float w, float h)
{
    /**
     * TODO
     * - Offset Sprite. If using the same Texture offset the sprite coordinates.
     */
    SDL_Rect srcrect = { x: sprite.width * sprite.x, y : sprite.width * sprite.y, w : sprite.width, h : sprite.height };
    SDL_FRect dstrect = { x: x * scaleW, y : y * scaleH, w : w * scaleW, h : h * scaleW };
    SDL_RenderCopyF(this->renderer, sprite.source->texture, &srcrect, &dstrect);
}
void LightCanvas::Renderer::DrawSprite(Sprite sprite, const Vector position)
{
    DrawSprite(sprite, position.x, position.y, sprite.width, sprite.height);
}
void LightCanvas::Renderer::DrawSprite(Sprite sprite, const Vector position, const Vector size) {
    DrawSprite(sprite, position.x, position.y, size.x, size.y);
}
void LightCanvas::Renderer::DrawSprite(Sprite sprite, float x, float y)
{
    DrawSprite(sprite, x, y, sprite.width, sprite.height);
}



void LightCanvas::Renderer::DrawText(const StaticText& text, const Vector& position)
{
    SDL_FRect dstRect;
    dstRect.x = position.x * scaleW;
    dstRect.y = position.y * scaleH;
    dstRect.w = text.size.x * scaleW;
    dstRect.h = text.size.y * scaleH;
    SDL_RenderCopyF(this->renderer, text.textureData, NULL, &dstRect);
}
void LightCanvas::Renderer::DrawText(const Text& text, const Vector& position)
{
    SDL_FRect dstRect;
    dstRect.x = position.x * scaleW;
    dstRect.y = position.y * scaleH;
    dstRect.w = text.size.x * scaleW;
    dstRect.h = text.size.y * scaleH;
    SDL_RenderCopyF(this->renderer, text.textureData, NULL, &dstRect);
}
void LightCanvas::Renderer::DrawText(const Text& text, const Vector& position, const Vector& size)
{
    SDL_FRect dstRect;
    dstRect.x = position.x * scaleW;
    dstRect.y = position.y * scaleH;
    dstRect.w = size.x * scaleW;
    dstRect.h = size.y * scaleH;
    SDL_RenderCopyF(this->renderer, text.textureData, NULL, &dstRect);
}

SDL_Texture* LightCanvas::Renderer::LoadTexture(const char* path)
{
    // Load a Surface and copy pixels
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return text;
}

int LightCanvas::Renderer::ChangeRenderTarget(SDL_Texture* texture, int w, int h)
{
    int result = SDL_SetRenderTarget(renderer, texture);

    SDL_RenderSetLogicalSize(renderer, w == 0 ? this->screenWidth : w, h == 0 ? this->screenHeight : h);

    return result;
}

bool LightCanvas::Renderer::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    return SDL_RenderClear(renderer);
}

void LightCanvas::Renderer::HandleWindowEvent(const SDL_Event* event)
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
        scaleH = 1;
        scaleW = 1;
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
