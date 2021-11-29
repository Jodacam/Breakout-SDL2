#include "UIElements.h"
void GameEngine::UIImage::Render(GameEngine::Renderer *renderer)
{
    renderer->DrawImage(image.get(), position, size);
}