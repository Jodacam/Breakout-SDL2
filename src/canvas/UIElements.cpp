#include "UIElements.h"
#include "../resourceManager/AssetsManager.h"
void GameEngine::UIElement::SetPosition(const Vector &pos)
{
    position = pos;
    isDirty = true;
}

void GameEngine::UIElement::SetSize(const Vector &s)
{
    position = s;
    isDirty = true;
}

//TODO CHANGE
GameEngine::UIImage::UIImage(std::string asset)
{
    Sprite *s = new Sprite();
    if (AssetManager::GetInstance()->GetSprite(s, asset)) {
        image = std::shared_ptr<Sprite>(s);
        position = Vector(0,0);
        size = Vector(image->width,image->height);
    }
}

GameEngine::UIImage::UIImage(std::string asset,Vector position)
{
    Sprite *s = new Sprite();
    if (AssetManager::GetInstance()->GetSprite(s, asset)) {
        image = std::shared_ptr<Sprite>(s);
        this->position = position;
        size = Vector(image->width,image->height);
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
