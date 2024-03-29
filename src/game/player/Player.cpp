#include "Player.h"
#include "../../engine/consts/game.h"
void LightCanvas::Player::Render(LightCanvas::Renderer *renderer)
{
    //Draw the palet.
    renderer->DrawSprite(&this->sprite, this->position.x, this->position.y);
}

void LightCanvas::Player::Update(LightCanvas::EventManager *eventManager, Ball *ball, float dt)
{
    GameController *controller = eventManager->GetController();

    float delta = speed * dt * controller->GetAxisValue(GameAxisType::LEFT_X);
    float newX = position.x + delta;
    //Check collisions
    if (newX + width < GAME_FIELD_POSITIVE_X_LIMIT && newX > GAME_FIELD_NEGATIVE_X_LIMIT)
    {
        position.x = newX;
        if (ball->GetIsOnRacket())
        {
            ball->SetPosition(Vector(ball->GetPosition().x + delta, ball->GetPosition().y));
            if (controller->GetButton(GameButtonType::A).isPressed)
            {
                ball->SetIsOnRacket(false);
                int xDir = delta >= 0 ? 1 : -1;
                Vector direction = Vector(xDir*0.5,-0.5);

                ball->SetDirection(direction.Normalized());
            }
        }
    }
}