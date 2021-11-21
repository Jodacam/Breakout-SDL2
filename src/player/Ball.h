#ifndef _BALL_H_
#define _BALL_H_
#include <SDL2/SDL.h>
#include "../render/SDLRender.h"
#include "../resourceManager/AssetsManager.h"
#include "../math/Vector.h"
#include "../game/Block.h"
#include "Player.h"
namespace GameEngine
{
    class Player;
    class Ball
    {
    private:
        Image *sprite;
        Vector position;
        float speed;
        Vector direction;
        bool isOnRacket = false;
        float collisionCooldown = 0.0f;
        //Colision radius
        float radius = 2.5;

    public:
        Ball(float x, float y) : position(x, y)
        {
            sprite = AssetManager::GetInstance()->AddTexture("resources/img/Ball.png", "ball");
        }
        Ball(Vector position) : position(position)
        {
            sprite = AssetManager::GetInstance()->AddTexture("resources/img/Ball.png", "ball");
        }
        void Update(float dt, GameEngine::Player *player);
        void Render(Renderer *renderer);
        Vector GetPosition() { return position; }
        Vector GetDirection() { return direction; }
        float GetSpeed() { return speed; }
        bool CheckBlockCollision(Block *block);
        bool SetIsOnRacket(bool a)
        {
            isOnRacket = a;
            return isOnRacket;
        }
        bool GetIsOnRacket()  { return isOnRacket; }
        Vector SetDirection(Vector direction)
        {
            this->direction = direction;
            return this->direction;
        }
        Vector SetDirection(float x, float y)
        {
            direction = Vector(x, y);
            return this->direction;
        }
        Vector SetPosition(Vector position)
        {
            this->position = position;
            return this->position;
        }
        Vector SetPosition(float x, float y)
        {
            position = Vector(x, y);
            return this->position;
        }
        float SetSpeed(float speed)
        {
            this->speed = speed;
            return this->speed;
        }
    };

}

#endif