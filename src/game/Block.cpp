#include "Block.h"
#include "../resourceManager/assetsManager.h"

GameEngine::Block::Block(Vector position,std::string sprite) {

    this->sprite = GameEngine::AssetManager::getInstance()->getTexture(sprite.c_str());
    this->position = position;
    int w,h;
    SDL_QueryTexture(this->sprite, NULL,NULL,&w, &h);
    this->size = Vector(w,h);
}

void GameEngine::Block::Render(GameEngine::Renderer *renderer) {
    renderer->DrawImage(this->sprite,this->position,this->size);
}