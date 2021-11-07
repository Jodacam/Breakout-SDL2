#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_
#include <iostream>
#include <SDL.h>
#include "input/GameController.h"
#include <SDL_gamecontroller.h>
namespace GameEngine
{

    class EventManager
    {

    private: //
        SDL_Event *actualEvent;
        const Uint8 *keyBoardState;
        GameController *gameController;
        static EventManager *instance;

    public:
        bool ManageEvents();
        GameController * GetController(){return gameController;}
        EventManager()
        {
            this->gameController = new GameController(); 
        }
        static EventManager* Instance();
        int PollEvent(SDL_Event *event);
        bool ReadKeyBoard();
        bool IsKeyPress(Uint8 key);
        ~EventManager() { delete gameController; }
    };

}
#endif