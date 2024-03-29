#ifndef _BALL_H_
#define _BALL_H_
#include <SDL2/SDL.h>
#include "../../engine/render/SDLRender.h"
#include "../../engine/resourceManager/AssetsManager.h"
#include "../../engine/math/Vector.h"
#include "../Block.h"
#include "Player.h"
namespace LightCanvas
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
            AssetManager::GetInstance()->AddTexture("resources/img/Ball.png", "ball");
            sprite =  AssetManager::GetInstance()->getTexture("ball");
        }
        Ball(Vector position) : position(position)
        {
            AssetManager::GetInstance()->AddTexture("resources/img/Ball.png", "ball");
            sprite =  AssetManager::GetInstance()->getTexture("ball");
        }
        void Update(float dt, LightCanvas::Player *player);
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