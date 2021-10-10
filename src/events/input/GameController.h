#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_
#include <SDL_gamecontroller.h>
namespace GameEngine
{
    class GameController {

        private:
            SDL_GameController* controller;
        public:
            SDL_GameController* GetNativeController() { return controller; }
    };
}
#endif