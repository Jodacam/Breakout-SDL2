#ifndef __SPRITENODE_H__
#define __SPRITENODE_H__
#include "../Node.h"
#include "../../render/Graphics.h"
#include "../../resourceManager/AssetsManager.h"
namespace GameEngine {
    class SpriteNode : public Node {
    public:
        SpriteNode(const std::string& name) : Node(name) {};
        SpriteNode(const std::string& name, const std::string& spriteResource) : Node(name) {
            sprite = AssetManager::GetInstance()->GetSprite(spriteResource);
        };
        virtual void Update(float dt);
        virtual void Render(GameEngine::Renderer* renderer);
    protected:
        Sprite sprite;

    };
}

#endif