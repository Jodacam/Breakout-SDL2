#include "Ball.h"
#include "../../engine/consts/game.h"
#include "../../engine/consts/functions.h"
#include "../../engine/audio/AudioManager.h"
void LightCanvas::Ball::Update(float dt, LightCanvas::Player *player)
{
    //If the ball is stuck on the racket move it like the player is moving.
    if (isOnRacket)
    {
        return;
    }

    Vector lastPosition = Vector(position);
    position = position + (direction * (speed * dt));
    //Check with player position
    Vector player_position = player->GetPosition();
    Vector center = Vector(position.x + radius, position.y + radius);
    float vertex[4] = {player_position.x, player_position.x + player->width, player_position.y, player_position.y + player->height};
    if (collisionCooldown <= 0 && LightCanvas::CheckCicleRectangleCollision(center, radius, vertex))
    {
        collisionCooldown = 0.25f;
        direction = Vector(direction.x, -direction.y);
        std::cout << "Position: " << position << " Direction: " << direction << " Speed " << speed << std::endl;
        position = lastPosition;
        AudioManager::GetInstance()->PlaySoundEffect("bounce");
    }
    //Check the Wall position here.
    //Check top wall position
    else if (position.y < 0)
    {
        direction = Vector(direction.x, -direction.y);
        position = lastPosition;
    }
    //Check left wall position
    else if (position.x < GAME_FIELD_NEGATIVE_X_LIMIT)
    {

        //Change the direction.
        //When it collides with a wall use a 90º angle with the direction.
        direction = Vector(-direction.x, direction.y);
        position = lastPosition;
    }
    //Check right wall position
    else if (position.x + radius * 2 > GAME_FIELD_POSITIVE_X_LIMIT)
    {
        direction = Vector(-direction.x, direction.y);
        position = lastPosition;
    }

    if (collisionCooldown > 0)
    {
        collisionCooldown -= dt;
        if (collisionCooldown < 0)
            collisionCooldown = 0;
    }
}
void LightCanvas::Ball::Render(LightCanvas::Renderer *renderer)
{
    renderer->DrawImage(this->sprite, position);
}

bool LightCanvas::Ball::CheckBlockCollision(Block *block)
{
    Vector block_pos = block->GetPosition();
    Vector block_size = block->GetSize();
    float vertex[4] = {block_pos.x, block_pos.x + block_size.x, block_pos.y, block_pos.y + block_size.y};

    Vector center = Vector(position.x + radius, position.y + radius);
    //New Type check.
    //Check if there is a collision. Then check where the colision is happening using vectors. After that use the reflect vector to change the direction.
    bool isColiding = LightCanvas::CheckCicleRectangleCollision(center, radius, vertex);

    if (isColiding)
    {
        //Check were the colision is happening.
        float closestX = LightCanvas::clamp(center.x, vertex[0], vertex[1]);
        float closestY = LightCanvas::clamp(center.y, vertex[2], vertex[3]);

        float distanceX = center.x - closestX;
        float distanceY = center.y - closestY;
        Vector distance = Vector(distanceX, distanceY);
        Vector dNormal = Vector(-distanceY, distanceX);

        float normal_angle = std::atan2(dNormal.y, dNormal.x);
        float incoming_angle = std::atan2(direction.y, direction.x);

        float theta = normal_angle - incoming_angle;

        //Here we can add a bit a random angle.
        direction = direction.Rotate(2 * theta).Normalized();
    }

    return isColiding;
}
