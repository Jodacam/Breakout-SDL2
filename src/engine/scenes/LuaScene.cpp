#include "LuaScene.h"
#include "../events/EventManager.h"
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
    //Register all the Lua Related functions.
    RegisterFunctions();
    //Execute the scene main script
    if (!luaVM.ExecuteFile(script)) {
        std::cout << luaVM.GetError() << std::endl;
    }
}

void GameEngine::LuaScene::RegisterFunctions() {

    luaL_newmetatable(luaVM.GetInternalVM(), "Vector");

    if (!luaVM.ExecuteFile("resources/scripts/main.lua")) {
        std::cout << luaVM.GetError() << std::endl;
    }
    luaVM.RegisterBasics();
    luaVM.RegisterFunction("LCCP_CreateLuaObject", LCCP_CreateLuaObject);

    //Create the Scene Metatable.
    RegisterMetaTable();


    luaVM.RegisterFunction("LCCP_GetActualScene", [this]
    (GameEngine::ScriptManager* m)
        {
            auto _lua = m->GetInternalVM();
            GameEngine::Lua_Scene* s = (GameEngine::Lua_Scene*)lua_newuserdata(_lua, sizeof(GameEngine::Lua_Scene));
            new (s) GameEngine::Lua_Scene(this);
            luaL_setmetatable(_lua, "Scene");
            return 1;
        }
    );
}

#pragma region Lua Functions
int AddNodeToScene(lua_State* L) {

    if (!lua_isuserdata(L, 1) || !lua_isuserdata(L, 2))  throw std::invalid_argument("Not valid parameters");

    GameEngine::Lua_Scene* scene = (GameEngine::Lua_Scene*)lua_touserdata(L, 1);
    GameEngine::Lua_Node* node = (GameEngine::Lua_Node*)lua_touserdata(L, 2);

    scene->GetScene()->AddNode(node->GetInternal());

    return 0;

}
int RegisterUpdate(lua_State* L) {
    GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    if (!lua_isuserdata(L, 1) || !lua_isfunction(L, 2))  throw std::invalid_argument("Not valid parameters");

    GameEngine::Lua_Scene* scene = (GameEngine::Lua_Scene*)lua_touserdata(L, 1);

    //m->CallFunction("LC_RegisterUpdate",scene->GetScene(),lua_to(L,2));
    return 0;
}

int GetNative(lua_State* L) {
    GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    if (!lua_isuserdata(L, 1))  throw std::invalid_argument("Not valid parameters");
    GameEngine::Lua_Scene* scene = (GameEngine::Lua_Scene*)lua_touserdata(L, 1);
    return m->PushValue(scene->GetScene());
}
#pragma endregion

void GameEngine::LuaScene::RegisterMetaTable() {
    auto L = luaVM.GetInternalVM();
    lua_newtable(L);
    int index = lua_gettop(L);
    lua_pushvalue(L, index);
    lua_setglobal(L, "LC_Scene");

    //Define all functions on one place
    luaVM.SetTableValue("AddNode", AddNodeToScene);
    luaVM.SetTableValue("RegisterUpdate", RegisterUpdate);
    luaVM.SetTableValue("GetNative", GetNative);

    luaL_newmetatable(L, "Scene");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, index);
    lua_settable(L, -3);
}

void GameEngine::LuaScene::Update(float dt)
{
    //Each update, update the Input.

    

    for (auto&& i : nodes)
    {
        i->Update(dt);
    }

    luaVM.CallTableFunction("Light_Canvas" ,"CallUpdate", this, dt);

    
    

}

void GameEngine::LuaScene::Render(GameEngine::Renderer* renderer)
{
    for (auto&& i : nodes)
    {
        i->Render(renderer);
    }

}

void GameEngine::LuaScene::OnStart()
{

}