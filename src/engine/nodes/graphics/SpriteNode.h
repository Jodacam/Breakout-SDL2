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
        bool SetSprite(const std::string& sprite);
    protected:
        Sprite sprite;

    };

    class Lua_SpriteNode :public Lua_Node {
    public:
        Lua_SpriteNode(SpriteNode* node) :Lua_Node(node) {};
        Lua_SpriteNode(std::shared_ptr<SpriteNode> node) :Lua_Node(node.get()) {}; 

        static int CreateOne(GameEngine::ScriptManager* m);
        static void CreateLuaMetaInfo(GameEngine::ScriptManager* m);
        static int CreateLuaMetaTableFunctions(GameEngine::ScriptManager* m);
    };
}

#endif