#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_
#include <SDL.h>

namespace GameEngine {


    class EventManager {
        
        private: //
            SDL_Event* actualEvent;
            const Uint8* keyBoardState;
        public:
            bool ManageEvents();
            EventManager() {}
            int PollEvent(SDL_Event* event);
            bool ReadKeyBoard();
            bool IsKeyPress(Uint8 key);
    };

}
#endif