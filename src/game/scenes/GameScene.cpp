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
        std::stringstream s;
        s << "Lives: " << lives;
        score.SetText(s.str());
        ball->SetPosition(Vector(player->GetPosition().x + (player->width / 2) - 2.5, player->GetPosition().y - 5));
        ball->SetIsOnRacket(true);
    }
}

void GameEngine::GameScene::OnStart()
{
    score.SetText("Lives: 3", true);
    score.size = score.size*1.5;
    background = GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Hexagon_Pattern.png", "background");
    borders[0] = GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Border_Left.png", "leftborder");
    borders[1] = GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Border_Right.png", "rightborder");
    borders[2] = GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Border_Top.png", "topborder");
    player->SetX(220);
    player->SetY(250);
    ball->SetSpeed(100);
    ball->SetIsOnRacket(true);
    ball->SetPosition(Vector(player->GetPosition().x + (player->width / 2) - 2.5, player->GetPosition().y - 5));
    //Fill the screen with the blocks.
    int initialHeight = 50;
    int row_width = 24;
    int row_height = 9;

    //Init the block colors
    AssetManager::GetInstance()->AddTexture("resources/img/Block.png", "block");
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
    //auto t = renderer->GenerateStaticText("Hello world");
    renderer->DrawImage(background, 120, 0, 240, 277);
    ball->Render(renderer);
    player->Render(renderer);

    for (int i = 0; i < blocks.size(); i++)
    {
        blocks[i]->Render(renderer);
    }

    renderer->DrawImage(borders[0],GAME_FIELD_NEGATIVE_X_LIMIT-6,7);
    renderer->DrawImage(borders[1],GAME_FIELD_POSITIVE_X_LIMIT,7);
    renderer->DrawImage(borders[2],GAME_FIELD_NEGATIVE_X_LIMIT-6,0);

    renderer->DrawText(score, Vector(0, 0));
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