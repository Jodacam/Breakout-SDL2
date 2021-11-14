#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "../../player/Player.h"
#include "../../player/Ball.h"
#include "../Block.h"
#include <SDL2/SDL.h>
#include "Scene.h"
#include <vector>

const int MAX_BLOCK_PER_ROW = 10;
const int MAX_BLOCK_ROWS = 5;
const float SPEED_INCREMENT = 2.0f;
namespace GameEngine
{

    class GameScene : public Scene
    {
    private:
        /* data */
        Player *player;
        Ball *ball;
        Image *background;
        std::vector<Block *> blocks;
        int lives = 3;
    public:
        GameScene()
        {
            this->player = new GameEngine::Player();
            this->ball = new GameEngine::Ball(220, 280);
            blocks.reserve(MAX_BLOCK_ROWS*MAX_BLOCK_PER_ROW);
        }

        void Render(GameEngine::Renderer *renderer);
        void Update(float dt);
        void OnAdd();
        void OnStart();
        ~GameScene();
    };
}
#endif