#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
namespace GameEngine {

    class Player {
        private:
            int x = 0;
            int y = 0;
        public:
            Player() {
            }
            bool SetSprite();
            inline int SetX(int x) { this->x = x; return x;}
            inline int SetY(int y) { this->y = y; return y;}


    };


}

#endif