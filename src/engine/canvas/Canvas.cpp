#include "Canvas.h"
#include <algorithm>
LightCanvas::Canvas::Canvas(int w, int h)
{
    texture = SDL_CreateTexture(Renderer::GetInstance()->GetInternalRender(), SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    width = w;
    height = h;
}

LightCanvas::Canvas::~Canvas()
{
    SDL_DestroyTexture(texture);
}

void LightCanvas::Canvas::Update(float dt)
{

    //Internal update.

    //Update each UI element.
    for (auto &&i : elements)
    {
        i->Update(dt);
    }
}

void LightCanvas::Canvas::Render(LightCanvas::Renderer *renderer)
{

    //Check first if any of the elements it's dirty.
    bool isDirty = std::any_of(elements.begin(), elements.end(), [](auto e)
                               { return e->GetIsDirty(); });

    if (isDirty)
    {
        //Change the render target.
        renderer->ChangeRenderTarget(texture,width,height);

        SDL_SetRenderDrawColor(renderer->GetInternalRender(), 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        SDL_RenderClear(renderer->GetInternalRender());
        for (auto &&i : elements)
        {
            i->Render(renderer);
        }
        //Change the render target and draw the new Canvas Texture.
        renderer->ChangeRenderTarget(NULL);
        SDL_SetRenderDrawColor(renderer->GetInternalRender(), 0, 0, 0, 255);
    }

    renderer->DrawFillScreen(texture);
}

void LightCanvas::Canvas::AddElement(const std::shared_ptr<LightCanvas::UIElement> &element)
{
     elements.push_back(element);
}


