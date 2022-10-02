#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "../player/Player.h"
#include "../player/Ball.h"
#include "../Block.h"
#include <SDL2/SDL.h>
#include "../../engine/scenes/Scene.h"
#include <vector>
#include <sstream>

const int MAX_BLOCK_PER_ROW = 10;
const int MAX_BLOCK_ROWS = 5;
const float SPEED_INCREMENT = 2.0f;
namespace LightCanvas
{

    class GameScene : public Scene
    {
    private:
        /* data */
        Player *player;
        Ball *ball;
        Image *background;
        Image *borders[3];
        std::vector<Block *> blocks;
        Text score;
        int lives = 3;
    public:
        GameScene()
        {
            this->player = new LightCanvas::Player();
            this->ball = new LightCanvas::Ball(220, 280);
            blocks.reserve(MAX_BLOCK_ROWS*MAX_BLOCK_PER_ROW);
        }

        void Render(LightCanvas::Renderer *renderer);
        void Update(float dt);
        void OnAdd();
        void OnStart();
        ~GameScene();
    };
}
#endif