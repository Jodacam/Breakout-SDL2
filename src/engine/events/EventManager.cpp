#include "EventManager.h"

bool LightCanvas::EventManager::ManageEvents()
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

int LightCanvas::EventManager::PollEvent(SDL_Event *event) {
    
    int result = SDL_PollEvent(event);

    return result;

}

bool LightCanvas::EventManager::UpdateInput(){
    keyBoardState = SDL_GetKeyboardState(NULL);
    gameController->UpdateControllerState();
    return true;
}

bool LightCanvas::EventManager::IsKeyPress(Uint8 key) {
    return (bool)keyBoardState[key];
}





LightCanvas::EventManager* LightCanvas::EventManager::instance = NULL;
LightCanvas::EventManager* LightCanvas::EventManager::Instance(){
    if(instance == NULL)
        instance = new LightCanvas::EventManager();
    return instance;
}