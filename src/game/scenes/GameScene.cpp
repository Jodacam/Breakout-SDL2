#include "GameScene.h"
#include "../../engine/audio/AudioManager.h"
#include "../../engine/consts/game.h"
void LightCanvas::GameScene::Update(float dt)
{
    LightCanvas::EventManager *eventManager = LightCanvas::EventManager::Instance();
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

void LightCanvas::GameScene::OnStart()
{
    score.SetText("Lives: 3", true);
    score.size = score.size*1.5;

    //Preload this and get it later.
    background = LightCanvas::AssetManager::GetInstance()->getTexture("background");
    borders[0] = LightCanvas::AssetManager::GetInstance()->getTexture("leftborder");
    borders[1] = LightCanvas::AssetManager::GetInstance()->getTexture("rightborder");
    borders[2] = LightCanvas::AssetManager::GetInstance()->getTexture("topborder");
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

    //Play the music.
    AudioManager::GetInstance()->PlayMusic(*(AssetManager::GetInstance()->GetSong("default").get()),true);

}

void LightCanvas::GameScene::Render(LightCanvas::Renderer *renderer)
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

void LightCanvas::GameScene::OnAdd()
{
    std::cout << "Añadida escena de juego" << std::endl;
}

LightCanvas::GameScene::~GameScene()
{
    delete player;
    delete ball;
}