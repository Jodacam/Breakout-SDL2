#include "Block.h"
#include <resourceManager/AssetsManager.h>

GameEngine::Block::Block(Vector position,std::string sprite) {

    this->sprite = GameEngine::AssetManager::GetInstance()->getTexture(sprite.c_str());
    this->position = position;
    this->size = Vector(this->sprite->width,this->sprite->height);
}

void GameEngine::Block::Render(GameEngine::Renderer *renderer) {
    renderer->DrawImage(this->sprite,this->position,this->size);
}