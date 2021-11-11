#include "GameScene.h"
#include "../../consts/game.h"
void GameEngine::GameScene::Update(float dt)
{
    GameEngine::EventManager *eventManager = GameEngine::EventManager::Instance();
    player->Update(eventManager, ball, dt);
    //Comprobamos las colisiones.
    for (int i = 0; i < blocks.size(); i++)
    {
        bool isColliding = ball->CheckBlockCollision(blocks[i]);
        if (isColliding)
        {
            auto element = blocks[i];
            blocks.erase(blocks.begin() + i);
            ball->SetSpeed(ball->GetSpeed() + SPEED_INCREMENT);
            delete element;
            break;
        }
    }

    ball->Update(dt, player);

    auto ball_position = ball->GetPosition();

    if (ball_position.y > GAME_FIELD_H)
    {
        lives--;
        ball->SetPosition(Vector(player->GetPosition().x + 10, player->GetPosition().y - 5));
        ball->SetIsOnRacket(true);
    }
}

void GameEngine::GameScene::OnStart()
{
    background = GameEngine::AssetManager::getInstance()->AddTexture("resources/img/Hexagon_Pattern.png", "background");
    player->SetX(220);
    player->SetY(230);
    ball->SetSpeed(100);
    ball->SetIsOnRacket(true);
    ball->SetPosition(Vector(230, 230 - 5));
    //Fill the screen with the blocks.
    int initialHeight = 50;
    int row_width = 24;
    int row_height = 9;

    //Init the block colors
    AssetManager::getInstance()->AddTexture("resources/img/Block.png", "block");
    for (int j = 0; j < MAX_BLOCK_ROWS; j++)
    {
        for (int i = 0; i < MAX_BLOCK_PER_ROW; i++)
        {
            auto block = new Block(Vector(GAME_FIELD_NEGATIVE_X_LIMIT + row_width * i, initialHeight + (row_height * j)), "block");
            blocks.push_back(block);
        }
    }
}

void GameEngine::GameScene::Render(GameEngine::Renderer *renderer)
{

    renderer->DrawImage(background, 120, 0, 240, 320);
    ball->Render(renderer);
    player->Render(renderer);

    for (int i = 0; i < blocks.size(); i++)
    {
        blocks[i]->Render(renderer);
    }
}

void GameEngine::GameScene::OnAdd()
{
    std::cout << "Añadida escena de juego" << std::endl;
}

GameEngine::GameScene::~GameScene()
{
    delete player;
    delete ball;
}