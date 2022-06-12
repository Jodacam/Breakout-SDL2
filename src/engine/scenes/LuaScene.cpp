#include "LuaScene.h"

int LCCP_CreateLuaObject(GameEngine::ScriptManager* m)
{

    auto L = m->GetInternalVM();

    const char* name = lua_tostring(L, 1);

    void* obj = lua_newuserdata(L, sizeof(GameEngine::Node));

    new (obj) GameEngine::Node(name);

    std::cout << ((GameEngine::Node*)obj)->GetPosition() << std::endl;

    return 1;
}

void GameEngine::LuaScene::OnAdd()
{
    luaVM.RegisterFunction("LCCP_CreateLuaObject", LCCP_CreateLuaObject);
    luaVM.ExecuteFile("resources/scripts/main.lua");
    luaVM.CallFunction("CreateObject");
    luaVM.CallFunction("printName");
    auto obj = luaVM.GetGlobalUserData<Node>("sprite");
    std::cout << obj->GetPosition() << std::endl;

    auto sprite = AddNodeOfType<SpriteNode>("My first Sprite Node!","player");
    sprite->SetPosition(Vector(50,50));
    sprite->SetScale(Vector(1,1));

}

void GameEngine::LuaScene::RegisterFunctions() {
    
}

void GameEngine::LuaScene::Update(float dt)
{
    for (auto &&i : nodes)
    {
        i->Update(dt);
    }
    
}

void GameEngine::LuaScene::Render(GameEngine::Renderer* renderer)
{
    for (auto &&i : nodes)
    {
        i->Render(renderer);
    }
    
}

void GameEngine::LuaScene::OnStart()
{

}