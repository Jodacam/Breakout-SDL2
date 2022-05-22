#ifndef _LUASCENE_H_
#define _LUASCENE_H_
#include "Scene.h"
#include <vector>
#include <memory>
#include "../scripting/ScriptManager.h"
#include "../scripting/LuaGameObject.h"
namespace GameEngine
{
    class LuaScene : public Scene
    {
    public:
        LuaScene(std::string scriptPath) {
            script = scriptPath;
        }
        ~LuaScene(){};
        void OnAdd() override;
        void OnStart() override;
        void Update(float dt) override;
        void Render(GameEngine::Renderer *renderer) override;

    protected:
        ScriptManager luaVM;
        std::string script = "";
        std::vector<std::shared_ptr<LuaGameObject>> luaGameObjects;
        std::vector<std::shared_ptr<LuaGameObject>> objectsToDelete;
    };
}
#endif //_LUASCENE_H_