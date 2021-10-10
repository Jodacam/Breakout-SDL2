#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
#include "../render/SDLRender.h"
#include "../resourceManager/assetsManager.h"
#include "../events/eventManager.h"
namespace GameEngine {

    class Player {
        private:
            float x = 0;
            float y = 0;
            float speed = 100.0f;
            SDL_Texture * sprite;
        public:
            Player() {
                sprite = GameEngine::AssetManager::getInstance()->AddTexture("resources/img/Racket.png","player");
                x=100;
            }
            bool SetSprite();
            inline int SetX(int x) { this->x = x; return x;}
            inline int SetY(int y) { this->y = y; return y;}
            void Update(GameEngine::EventManager* eventManager, float dt = 1.0f/60.0f);
            void Render(GameEngine::Renderer* renderer);
            float SetSpeed(float speed) {this->speed = speed; return speed;};

    };


}

#endif