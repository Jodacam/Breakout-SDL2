#include "Block.h"
#include <resourceManager/AssetsManager.h>

LightCanvas::Block::Block(Vector position,std::string sprite) {

    this->sprite = LightCanvas::AssetManager::GetInstance()->getTexture(sprite.c_str());
    this->position = position;
    this->size = Vector(this->sprite->width,this->sprite->height);
}

void LightCanvas::Block::Render(LightCanvas::Renderer *renderer) {
    renderer->DrawImage(this->sprite,this->position,this->size);
}