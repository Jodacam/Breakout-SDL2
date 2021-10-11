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
        SDL_GameController *controller;
        GameController *gameController;

    public:
        bool ManageEvents();
        GameController * GetController(){return gameController;}
        EventManager()
        {

            controller = NULL;
            std::cout << "Numero de mandos:" << SDL_NumJoysticks() << std::endl;
            for (int i = 0; i < SDL_NumJoysticks(); ++i)
            {
                if (SDL_IsGameController(i))
                {
                    controller = SDL_GameControllerOpen(i);
                    if (controller)
                    {
                        std::cout << "El controlador se ha inicializado correctamente con la siguiente informacion : " << SDL_GameControllerGetType(controller) << ", " << SDL_GameControllerName(controller) << std::endl;
                        this->gameController = new GameController(controller);
                        break;
                    }
                    else
                    {
                        std::cout << "Ha ocurrido un error" << SDL_GetError() << std::endl;
                    }
                }
            }

            if (controller == NULL)
            {
                std::cout << "No se ha encontrado ningun mando" << SDL_GetError() << std::endl;
            }
        }
        int PollEvent(SDL_Event *event);
        bool ReadKeyBoard();
        bool IsKeyPress(Uint8 key);
        bool IsButtonPress(SDL_GameControllerButton button);
        ~EventManager() { delete gameController; }
    };

}
#endif