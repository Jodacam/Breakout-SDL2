#ifndef _LUASCENE_H_
#define _LUASCENE_H_
#include "Scene.h"
#include <vector>
#include <memory>
#include "../scripting/ScriptManager.h"
#include "../nodes/Node.h"
#include "../nodes/graphics/SpriteNode.h"
namespace GameEngine
{
    class LuaScene : public Scene
    {
    public:
        LuaScene(std::string scriptPath) {
            script = scriptPath;
            //Load the script.
        }
        ~LuaScene() {};
        void OnAdd() override;
        void OnStart() override;
        void Update(float dt) override;
        void Render(GameEngine::Renderer* renderer) override;

        template <typename N, typename ...Carg>
        std::shared_ptr<N> AddNodeOfType(Carg ...constructorArgs) {
            auto node = std::make_shared<N>(constructorArgs...);
            nodes.push_back(node);
            return node;
        };
        template <typename N>
        std::shared_ptr<N> AddNode(N* node) {
            
            auto n = std::shared_ptr<N>(node);
            nodes.push_back(n);
            return n;
        };

    protected:
        ScriptManager luaVM;
        std::string script = "";
        const char* l_updateScriptFunction = "Update";
        std::vector<std::shared_ptr<Node>> nodes;
        std::vector<std::shared_ptr<Node>> objectsToDelete;

        void RegisterFunctions();
        void RegisterMetaTable();
    };

    /**
     * @brief Wrapper class for scenes.
     *
     */
    class Lua_Scene {
    public:
        LuaScene* GetScene() const { return _scene; }
        Lua_Scene(LuaScene* scene) : _scene(scene) {};
    protected:
        LuaScene* _scene;
    };
}
#endif //_LUASCENE_H_