#include "player.h"

void GameEngine::Player::Render(GameEngine::Renderer *renderer)
{
    //Draw the palet.
    renderer->DrawImage(this->sprite, this->x, this->y);
}

void GameEngine::Player::Update(GameEngine::EventManager *eventManager, float dt)
{
    GameController *controller = eventManager->GetController();
    x += speed*dt*controller->GetAxisValue(GameAxisType::LEFT_X);
}