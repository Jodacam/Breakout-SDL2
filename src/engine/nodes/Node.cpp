#include "Node.h"
#include "lua/lua.h"


void GameEngine::Node::Update(float dt) {


    if (enable) {
        //Calls children Update.
        for (auto&& i : children)
        {
            i->Update(dt);
        }
    }

    //Move all the children
    children.insert(children.end(), std::make_move_iterator(toPush.begin()), std::make_move_iterator(toPush.end()));
    toPush.clear();
}


void GameEngine::Node::Render(GameEngine::Renderer* renderer) {
    if (!enable) return;
    //Calls children render.
    for (auto&& i : children) {
        i->Render(renderer);
    }
}


int GameEngine::Lua_Node::CreateOne(GameEngine::ScriptManager* m) {
    auto L = m->GetInternalVM();

    //Get The Node name.
    const char* name = lua_tostring(L, 2);
    Node* parent = nullptr;

    if (lua_islightuserdata(L, 3)) {
        parent = (Node*)lua_touserdata(L, 3);
    }

    //Creates the pointer.
    void* p = lua_newuserdata(L, sizeof(GameEngine::Lua_Node));
    Node* native_node = new GameEngine::Node(name);
    native_node->SetPosition(Vector(3, 4));
    new (p) GameEngine::Lua_Node(native_node);
    //Cast to the Node Class.
    luaL_setmetatable(L, "Node");

    return 1;
}

void GameEngine::Lua_Node::CreateLuaMetaInfo(GameEngine::ScriptManager* m) {

    auto L = m->GetInternalVM();

    lua_newtable(L);
    int index = lua_gettop(L);
    lua_pushvalue(L, index);
    lua_setglobal(L, "LC_Node");

    //Define all functions on one place
    Lua_Node::CreateLuaMetaTableFunctions(m);

    luaL_newmetatable(L, "Node");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, index);
    lua_settable(L, -3);
}


#pragma region Static Lua_Node Functions

int Lua_Node_SetPosition(lua_State* L) {

    //Get the info from parameters.

    int args = lua_gettop(L);
    //SceneManager is alwais an argument.

    GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    if (args <= 1) throw "Bad arguments";

    if (!lua_istable(L, 2)) throw "Not a table";

    lua_getfield(L, 2, "x");
    float x = lua_tonumber(L, -1);
    lua_getfield(L, 2, "y");
    float y = lua_tonumber(L, -1);

    GameEngine::Lua_Node* node = nullptr;
    if (lua_isuserdata(L, 1)) {
        node = (GameEngine::Lua_Node*)lua_touserdata(L, 1);
    };

    node->GetInternal()->SetPosition(GameEngine::Vector(x, y));

    return m->PushValue(GameEngine::Vector(x, y));
}

int Lua_Node_SetScale(lua_State* L) {

    //Get the info from parameters.

    int args = lua_gettop(L);
    GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    //SceneManager is alwais an argument.
    if (args <= 1) throw "Bad arguments";

    if (!lua_istable(L, 2)) throw "Not a table";

    lua_getfield(L, 2, "x");
    int x = lua_tonumber(L, -1);
    lua_getfield(L, 2, "y");
    int y = lua_tonumber(L, -1);

    GameEngine::Lua_Node* node = nullptr;
    if (lua_isuserdata(L, 1)) {
        node = (GameEngine::Lua_Node*)lua_touserdata(L, 1);
    };

    node->GetInternal()->SetScale(GameEngine::Vector(x, y));

    return m->PushValue(node->GetInternal()->GetScale());


}

int Lua_Node_SetRotation(lua_State* L) {

    //Get the info from parameters.
    int args = lua_gettop(L);
    GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    //SceneManager is alwais an argument.
    if (args <= 1) throw "Bad arguments";

    if (!lua_isnumber(L, 2)) throw "Not a number";
    auto rot = lua_tonumber(L, 2);

    GameEngine::Lua_Node* node = nullptr;
    if (lua_isuserdata(L, 1)) {
        node = (GameEngine::Lua_Node*)lua_touserdata(L, 1);
    };

    node->GetInternal()->SetRotation(rot);

    return m->PushValue((float)rot);


}

int Lua_Node_GetPosition(lua_State* L) {

    GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    GameEngine::Lua_Node* node = nullptr;
    if (lua_isuserdata(L, 1)) {
        node = (GameEngine::Lua_Node*)lua_touserdata(L, 1);
    };
    return m->PushValue(node->GetInternal()->GetPosition());

}
int Lua_Node_GetScale(lua_State* L) {

    GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    GameEngine::Lua_Node* node = nullptr;
    if (lua_isuserdata(L, 1)) {
        node = (GameEngine::Lua_Node*)lua_touserdata(L, 1);
    };
    return m->PushValue(node->GetInternal()->GetScale());

}
int Lua_Node_GetRotation(lua_State* L) {

    GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    GameEngine::Lua_Node* node = nullptr;
    if (lua_isuserdata(L, 1)) {
        node = (GameEngine::Lua_Node*)lua_touserdata(L, 1);
    };
    return m->PushValue(node->GetInternal()->GetRotation());

}

int Lua_Node_New(lua_State* L) {
    //Get The Node name.
    const char* name = lua_tostring(L, 1);
    GameEngine::Node* parent = nullptr;
    //Creates the pointer.
    void* p = lua_newuserdata(L, sizeof(GameEngine::Lua_Node));
    GameEngine::Node* native_node = new GameEngine::Node(name);
    new (p) GameEngine::Lua_Node(native_node);
    //Cast to the Node Class.
    luaL_setmetatable(L, "Node");

    return 1;
}
#pragma endregion

int GameEngine::Lua_Node::CreateLuaMetaTableFunctions(GameEngine::ScriptManager* m) {
    auto L = m->GetInternalVM();

    //Getters
    m->SetTableValue("GetPosition", Lua_Node_GetPosition);
    m->SetTableValue("GetScale", Lua_Node_GetScale);
    m->SetTableValue("GetRotation", Lua_Node_GetRotation);
    //Setters
    m->SetTableValue("SetPosition", Lua_Node_SetPosition);
    m->SetTableValue("SetScale", Lua_Node_SetScale);
    m->SetTableValue("SetRotation", Lua_Node_SetRotation);


    //Utility
    m->SetTableValue("New",Lua_Node_New);

    return 0;
}