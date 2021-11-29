#include "Canvas.h"
#include <algorithm>
GameEngine::Canvas::Canvas(int w, int h)
{   
    texture = SDL_CreateTexture(Renderer::GetInstance()->GetInternalRender(),SDL_PIXELFORMAT_RGBA4444,SDL_TEXTUREACCESS_TARGET,w,h);
}

GameEngine::Canvas::~Canvas()
{
    SDL_DestroyTexture(texture);
}

void GameEngine::Canvas::Update(float dt)
{

    //Internal update.

    //Update each UI element.
    for (auto &&i : elements)
    {
        i->Update(dt);
    }
}

void GameEngine::Canvas::Render(GameEngine::Renderer *renderer)
{

    //Check first if any of the elements it's dirty.
    bool isDirty = std::any_of(elements.begin(), elements.end(), [](auto e)
                               { return e->GetIsDirty(); });

    if (isDirty)
    {
        //Change the render target.
        renderer->ChangeRenderTarget(texture);
        for (auto &&i : elements)
        {
            i->Render(renderer);
        }
        //Change the render target and draw the new Canvas Texture.
        renderer->ChangeRenderTarget(NULL);
    }
}