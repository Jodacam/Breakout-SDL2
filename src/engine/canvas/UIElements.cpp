#include "UIElements.h"
#include "../resourceManager/AssetsManager.h"
void GameEngine::UIElement::SetPosition(const Vector &pos)
{
    position = pos;
    isDirty = true;
}

void GameEngine::UIElement::SetSize(const Vector &s)
{
    size = s;
    isDirty = true;
}

#pragma region UIImage
// TODO CHANGE
GameEngine::UIImage::UIImage(std::string asset)
{
    Sprite *s = new Sprite();
    if (AssetManager::GetInstance()->GetSprite(s, asset))
    {
        image = std::shared_ptr<Sprite>(s);
        position = Vector(0, 0);
        size = Vector(image->width, image->height);
    }
}

GameEngine::UIImage::UIImage(std::string asset, const Vector &position)
{
    Sprite *s = new Sprite();
    if (AssetManager::GetInstance()->GetSprite(s, asset))
    {
        image = std::shared_ptr<Sprite>(s);
        this->position = position;
        size = Vector(image->width, image->height);
    }
}

void GameEngine::UIImage::Render(GameEngine::Renderer *renderer)
{
    renderer->DrawSprite(image.get(), position, size);
    isDirty = false;
}

void GameEngine::UIImage::Update(float dt)
{
}
#pragma endregion

#pragma region UIText

GameEngine::UIText::UIText(const std::string &t, const Vector &pos)
{
    text.SetText(t, true);
    position = pos;
    size = text.size;
}

GameEngine::UIText::UIText(const std::string &t, const Vector &pos, const Vector &s)
{
    text.SetText(t, true);
    position = pos;
    size = s;
}

bool GameEngine::UIText::SetText(const std::string &t,bool changeText) {
    isDirty = true;
    text.SetText(t, changeText);
    return true;
}

void GameEngine::UIText::Render(GameEngine::Renderer *renderer)
{
    renderer->DrawText(text,position,size);
    isDirty = false;
}

#pragma endregion
