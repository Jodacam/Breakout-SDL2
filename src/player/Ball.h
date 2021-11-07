#ifndef _BALL_H_
#define _BALL_H_
#include <SDL.h>
#include "../render/SDLRender.h"
#include "../resourceManager/AssetsManager.h"
#include "../math/Vector.h"
#include "../game/Block.h"
#include "Player.h"
namespace GameEngine
{

    class Ball
    {
    private:
        SDL_Texture *sprite;
        Vector position;
        float speed;
        Vector direction;
        bool isOnRacket = false;
        //Colision radius
        float radius = 2.5;

    public:
        Ball(float x, float y) : position(x, y) {
            sprite = AssetManager::getInstance()->AddTexture("resources/img/Ball.png","ball");
        }
        Ball(Vector position) : position(position) {
            sprite = AssetManager::getInstance()->AddTexture("resources/img/Ball.png","ball");
        }
        void Update(float dt,Player* player);
        void Render(Renderer *renderer);
        Vector GetPosition() { return position; }
        Vector GetDirection() { return direction; }
        float GetSpeed() { return speed; }
        bool CheckBlockCollision(Block *block);
        Vector SetDirection(Vector direction)
        {
            this->direction = direction;
            return this->direction;
        }
        Vector SetDirection(float x, float y) 
        {
            direction = Vector(x,y);
            return this->direction;
        }
        Vector SetPosition(Vector position)
        {
            this->position = position;
            return this->position;
        }
        Vector SetPosition(float x, float y)
        {
            position = Vector(x,y);
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