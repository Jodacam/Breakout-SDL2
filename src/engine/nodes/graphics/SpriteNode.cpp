#include "SpriteNode.h"

void GameEngine::SpriteNode::Update(float dt) {
    Node::Update(dt);
}

void GameEngine::SpriteNode::Render(GameEngine::Renderer* renderer) {
    Node::Render(renderer);
    renderer->DrawSprite(sprite, GetPosition(), Vector::LinearMultiply(GetScale(), Vector(sprite.width, sprite.height)));
}