#include "ScriptManager.h"
#include "../nodes/lua/all.h"
bool GameEngine::ScriptManager::open()
{
    // Load the virtual machine.
    _lua = luaL_newstate();
    // Load the lua standar library.
    luaL_openlibs(_lua);
    return true;
}

void GameEngine::ScriptManager::Close()
{
    lua_close(_lua);
}

bool GameEngine::ScriptManager::ExecuteCommand(const std::string& command)
{

    int return_code = luaL_dostring(_lua, command.c_str());

    if (return_code == LUA_OK)
    {
        _error = "";
        return true;
    }
    _error = lua_tostring(_lua, -1);
    return false;
}

bool GameEngine::ScriptManager::ExecuteFile(const std::string& path)
{
    int return_code = luaL_dofile(_lua, path.c_str());

    if (return_code == LUA_OK)
    {
        _error = "";
        return true;
    }
    _error = lua_tostring(_lua, -1);
    return false;
}

bool GameEngine::ScriptManager::LoadFile(const std::string& path)
{

    int return_code = luaL_loadfile(_lua, path.c_str());

    if (return_code == LUA_OK)
    {
        _error = "";
        return true;
    }
    _error = lua_tostring(_lua, -1);
    return false;
}

bool GameEngine::ScriptManager::CallFunction(const std::string& function)
{



    int return_code = lua_getglobal(_lua, function.c_str());

    if (!lua_isfunction(_lua, -1))
    {
        _error = lua_tostring(_lua, -1);
        return false;
    }

    return_code = lua_pcall(_lua, 0, 0, 0);

    if (return_code != LUA_OK)
    {
        // Obtain the error from the pile.
        _error = lua_tostring(_lua, -1);
        return false;
    }

    return true;
}

void GameEngine::ScriptManager::RegisterFunction(const std::string& name, lua_CFunction function)
{
    lua_register(_lua, name.c_str(), function);
}

void GameEngine::ScriptManager::RegisterFunction(const std::string& name, std::function<int(ScriptManager* scriptManager)> function)
{

    // Add the function by the name.

    functionMap.insert(std::make_pair(name, function));

    int arguments = PushValue(this) + PushValue(name);

    lua_pushcclosure(
        _lua,
        [](lua_State* L) -> int
        {
            // Obtain the name function by the context.
            GameEngine::ScriptManager* manager = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
            const char* name = lua_tostring(L, lua_upvalueindex(2));
            return manager->CallInternalFunction(name);
        },
        arguments);
    lua_setglobal(_lua, name.c_str());
}

void GameEngine::ScriptManager::RegisterNodeFunction(const std::string& node_name, std::function<int(ScriptManager* scriptManager)> fn) {
    types.push_back(fn);
    CallTableFunction("Light_Canvas", "RegisterType", (int)(types.size() - 1), node_name);
}

void GameEngine::ScriptManager::RegisterBasics() {

    //Register all basic types.
    GameEngine::Lua_Node::CreateLuaMetaInfo(this);
    GameEngine::Lua_SpriteNode::CreateLuaMetaInfo(this);

    this->RegisterNodeFunction("node", GameEngine::Lua_Node::CreateOne);
    this->RegisterNodeFunction("sprite", GameEngine::Lua_SpriteNode::CreateOne);


    this->RegisterFunction("LCCP_CreateNode", [this](GameEngine::ScriptManager* m)
        {
            auto L = m->GetInternalVM();
            int type = lua_tonumber(L, 1);
            return this->types[type](m);
        });

    this->RegisterFunction("LCCP_DeleteNode", [this](GameEngine::ScriptManager*)
        {

            //Obtain the node and clear it from his parent.
            //If the node has no parent it means it was a root node and it will no be "Real deleted".
            //You can use the Scene::DeleteNode if you are using scenes.
            return 0;
        });

    //Register the input functions.
    lua_getglobal(_lua, "Light_Canvas");
    int LC = lua_gettop(_lua);
    lua_getfield(_lua, LC, "Input");
    int LC_input = lua_gettop(_lua);

    SetTableValue("GetButton", [](lua_State* L)
        {
            if (!lua_isnumber(L, 1)) return 0;
            GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
            auto input = GameEngine::EventManager::Instance()->GetController()->GetButton(lua_tointeger(L, 1));
            m->PushValue(input);
            return 1;
        });
    SetTableValue("GetAxis", [](lua_State* L)
        {
            if (!lua_isnumber(L, 1)) return 0;
            GameEngine::ScriptManager* m = (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
            auto input = GameEngine::EventManager::Instance()->GetController()->GetAxisValue(lua_tointeger(L, 1));
            m->PushValue(input);
            return 1;
        });

    lua_settop(_lua, LC - 1);
}