#include "Text.h"
#include "SDLRender.h"
#pragma region StaticText
GameEngine::StaticText::~StaticText()
{
    if (textureData)
        SDL_DestroyTexture(textureData);
}
#pragma endregion StaticText

#pragma region Text

GameEngine::Text::Text(std::string t)
{
    textureData = Renderer::GetInstance()->GenerateTextTexture(t);
    text = t;
    int w, h;
    SDL_QueryTexture(textureData, NULL, NULL, &w, &h);
    size = Vector(w, h);
}
GameEngine::Text::Text(std::string t, Vector s)
{
    textureData = Renderer::GetInstance()->GenerateTextTexture(t);
    text = t;
    size = s;
}

GameEngine::Text::~Text()
{
    if (textureData)
        SDL_DestroyTexture(textureData);
}

void GameEngine::Text::SetText(std::string t, bool resize)
{

    //Clear the  previous texture.

    if (textureData)
        SDL_DestroyTexture(textureData);
    //Generate a new texture
    textureData = Renderer::GetInstance()->GenerateTextTexture(t);
    if (resize)
    {
        int w, h;
        SDL_QueryTexture(textureData, NULL, NULL, &w, &h);
        size = Vector(w, h);
    }

    text = t;
}

#pragma endregion Text