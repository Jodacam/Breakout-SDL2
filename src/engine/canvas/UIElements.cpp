#include "UIElements.h"
#include "../resourceManager/AssetsManager.h"
void LightCanvas::UIElement::SetPosition(const Vector &pos)
{
    position = pos;
    isDirty = true;
}

void LightCanvas::UIElement::SetSize(const Vector &s)
{
    size = s;
    isDirty = true;
}

#pragma region UIImage
// TODO CHANGE
LightCanvas::UIImage::UIImage(std::string asset)
{
    image = AssetManager::GetInstance()->GetSprite(asset);
    position = Vector(0, 0);
    size = Vector(image.width, image.height);
}

LightCanvas::UIImage::UIImage(std::string asset, const Vector &position)
{
    image = AssetManager::GetInstance()->GetSprite(asset);
    this->position = position;
    size = Vector(image.width, image.height);
}

void LightCanvas::UIImage::Render(LightCanvas::Renderer *renderer)
{
    renderer->DrawSprite(&image, position, size);
    isDirty = false;
}

void LightCanvas::UIImage::Update(float dt)
{
}
#pragma endregion

#pragma region UIText

LightCanvas::UIText::UIText(const std::string &t, const Vector &pos)
{
    text.SetText(t, true);
    position = pos;
    size = text.size;
}

LightCanvas::UIText::UIText(const std::string &t, const Vector &pos, const Vector &s)
{
    text.SetText(t, true);
    position = pos;
    size = s;
}

bool LightCanvas::UIText::SetText(const std::string &t,bool changeText) {
    isDirty = true;
    text.SetText(t, changeText);
    return true;
}

void LightCanvas::UIText::Render(LightCanvas::Renderer *renderer)
{
    renderer->DrawText(text,position,size);
    isDirty = false;
}

#pragma endregion
