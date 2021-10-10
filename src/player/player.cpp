#include "player.h"

void GameEngine::Player::Render(GameEngine::Renderer *renderer)
{
    //Draw the palet.
    renderer->DrawImage(this->sprite, this->x, this->y);
}

void GameEngine::Player::Update(GameEngine::EventManager *eventManager, float dt)
{

    if (eventManager->IsKeyPress(SDL_SCANCODE_A))
        x += speed * dt;
    if (eventManager->IsKeyPress(SDL_SCANCODE_D))
        x -= speed * dt;
}