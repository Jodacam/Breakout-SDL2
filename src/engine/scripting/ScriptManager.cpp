#include "ScriptManager.h"
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
