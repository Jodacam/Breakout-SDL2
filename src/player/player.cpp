#include "player.h"
#include "../consts/game.h"
void GameEngine::Player::Render(GameEngine::Renderer *renderer)
{
    //Draw the palet.
    renderer->DrawImage(this->sprite, this->position);
}

void GameEngine::Player::Update(GameEngine::EventManager *eventManager, float dt)
{
    GameController *controller = eventManager->GetController();
    int lastX = position.x;
    position.x += speed*dt*controller->GetAxisValue(GameAxisType::LEFT_X);
    //Check collisions
    if(position.x+width >= GAME_FIELD_POSITIVE_X_LIMIT || position.x <= GAME_FIELD_NEGATIVE_X_LIMIT ) {
        position.x = lastX;
    }
}