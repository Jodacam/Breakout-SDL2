#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
#include "../render/SDLRender.h"
#include "../resourceManager/AssetsManager.h"
#include "../events/EventManager.h"
#include "Ball.h"

namespace GameEngine {
    class Ball;
    class Player {
        private:
            Vector position;
            float x = 0;
            float y = 0;
            float speed = 300.0f;
            //Internal colision rectangle.
            //use Now, when animation is implemented,change to Sprite Class 
            SDL_Texture * sprite;
        public:
            int width = 0;
            int height = 0;
            Player() {
                position = Vector(0,0);
                sprite = GameEngine::AssetManager::getInstance()->AddTexture("resources/img/Racket.png","player");
                SDL_QueryTexture(sprite, NULL, NULL, &width, &height);
            }
            bool SetSprite();
            inline float SetX(float x) { this->position.x = x; return this->position.x;}
            inline float SetY(float y) { this->position.y = y; return position.y;}
            Vector GetPosition() {return position;}
            Vector SetPosition(Vector position) {this->position = position; return position;}
            void Update(GameEngine::EventManager* eventManager, GameEngine::Ball* ball,float dt = 1.0f/60.0f);
            void Render(GameEngine::Renderer* renderer);
            float SetSpeed(float speed) {this->speed = speed; return speed;};

    };


}

#endif