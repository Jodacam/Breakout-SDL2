#include "eventManager.h"

bool GameEngine::EventManager::ManageEvents()
{   
    while (SDL_PollEvent(actualEvent))
    {

        switch (actualEvent->type)
        {
            case SDL_QUIT:
                return false;
                break;
        }
    }
    return true;
}

int GameEngine::EventManager::PollEvent(SDL_Event *event) {
    
    int result = SDL_PollEvent(event);

    return result;

}

bool GameEngine::EventManager::ReadKeyBoard(){
    keyBoardState = SDL_GetKeyboardState(NULL);
    gameController->UpdateControllerState();
    return true;
}

bool GameEngine::EventManager::IsKeyPress(Uint8 key) {
    return (bool)keyBoardState[key];
}
bool GameEngine::EventManager::IsButtonPress(SDL_GameControllerButton button) {
    return (bool)SDL_GameControllerGetButton(controller,button);
}