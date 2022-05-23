#include "LuaScene.h"

int LCCP_CreateLuaObject(GameEngine::ScriptManager* m)
{

    auto L = m->GetInternalVM();
    GameEngine::LuaGameObject* obj = (GameEngine::LuaGameObject*)lua_newuserdata(L, sizeof(GameEngine::LuaGameObject));
    obj->pos = 10;
    return 1;
}

void GameEngine::LuaScene::OnAdd()
{

    luaVM.ExecuteFile("resources/scripts/main.lua");

    auto lamba = [](GameEngine::ScriptManager* manager) -> int
    {
        return 0;
    };

    luaVM.RegisterFunction("LCCP_CreateLuaObject", lamba);
    luaVM.CallFunction("CreateObject");
    luaVM.CallFunction("printName");
    auto obj = luaVM.GetGlobalUserData<LuaGameObject>("sprite");
    std::cout << obj->pos << std::endl;
}

void GameEngine::LuaScene::Update(float dt)
{
}

void GameEngine::LuaScene::Render(GameEngine::Renderer* renderer)
{
}

void GameEngine::LuaScene::OnStart()
{
}