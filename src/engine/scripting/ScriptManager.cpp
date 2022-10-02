#include "ScriptManager.h"
#include "../nodes/lua/all.h"
bool LightCanvas::ScriptManager::open()
{
    // Load the virtual machine.
    _lua = luaL_newstate();
    // Load the lua standar library.
    luaL_openlibs(_lua);
    return true;
}

void LightCanvas::ScriptManager::Close()
{
    lua_close(_lua);
}

bool LightCanvas::ScriptManager::ExecuteCommand(const std::string& command)
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

bool LightCanvas::ScriptManager::ExecuteFile(const std::string& path)
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

bool LightCanvas::ScriptManager::LoadFile(const std::string& path)
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

bool LightCanvas::ScriptManager::CallFunction(const std::string& function)
{



    lua_getglobal(_lua, function.c_str());

    if (!lua_isfunction(_lua, -1))
    {
        _error = lua_tostring(_lua, -1);
        return false;
    }

    int return_code = lua_pcall(_lua, 0, 0, 0);

    if (return_code != LUA_OK)
    {
        // Obtain the error from the pile.
        _error = lua_tostring(_lua, -1);
        return false;
    }

    return true;
}

void LightCanvas::ScriptManager::RegisterFunction(const std::string& name, lua_CFunction function)
{
    lua_register(_lua, name.c_str(), function);
}

void LightCanvas::ScriptManager::RegisterFunction(const std::string& name, std::function<int(ScriptManager* scriptManager)> function)
{

    // Add the function by the name.

    functionMap.insert(std::make_pair(name, function));

    int arguments = PushValue(this) + PushValue(name);

    lua_pushcclosure(
        _lua,
        [](lua_State* L) -> int
        {
            // Obtain the name function by the context.
            LightCanvas::ScriptManager* manager = (LightCanvas::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
            const char* name = lua_tostring(L, lua_upvalueindex(2));
            return manager->CallInternalFunction(name);
        },
        arguments);
    lua_setglobal(_lua, name.c_str());
}

void LightCanvas::ScriptManager::RegisterNodeFunction(const std::string& node_name, std::function<int(ScriptManager* scriptManager)> fn) {
    types.push_back(fn);
    CallTableFunction("Light_Canvas", "RegisterType", (int)(types.size() - 1), node_name);
}











#pragma region AssetManger functions
int LoadImage(lua_State* L) {
    LightCanvas::ScriptManager* m = (LightCanvas::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    //Two params.
    if (!lua_isstring(L, 1) && !lua_isstring(L, 2)) throw std::invalid_argument("Not valid parameters");
    LightCanvas::AssetManager::GetInstance()->AddTexture(lua_tostring(L, 1), lua_tostring(L, 2));
    m->PushValue(lua_tostring(L, 2));
    return 1;
}

int LoadSoundEffect(lua_State* L) {
    LightCanvas::ScriptManager* m = (LightCanvas::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    //Two params.
    if (!lua_isstring(L, 1) && !lua_isstring(L, 2)) throw std::invalid_argument("Not valid parameters");
    LightCanvas::AssetManager::GetInstance()->AddSoundEffect(lua_tostring(L, 1), lua_tostring(L, 2));
    m->PushValue(lua_tostring(L, 2));
    return 1;
}

int LoadSong(lua_State* L) {
    LightCanvas::ScriptManager* m = (LightCanvas::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
    //Two params.
    if (!lua_isstring(L, 1) && !lua_isstring(L, 2)) throw std::invalid_argument("Not valid parameters");
    LightCanvas::AssetManager::GetInstance()->AddSong(lua_tostring(L, 1), lua_tostring(L, 2));
    m->PushValue(lua_tostring(L, 2));
    return 1;
}
#pragma endregion



void LightCanvas::ScriptManager::RegisterBasics() {

    //Register all basic types.
    LightCanvas::Lua_Node::CreateLuaMetaInfo(this);
    LightCanvas::Lua_SpriteNode::CreateLuaMetaInfo(this);


    this->RegisterNodeFunction("node", LightCanvas::Lua_Node::CreateOne);
    this->RegisterNodeFunction("sprite", LightCanvas::Lua_SpriteNode::CreateOne);


    this->RegisterFunction("LCCP_CreateNode", [this](LightCanvas::ScriptManager* m)
        {
            auto L = m->GetInternalVM();
            int type = lua_tonumber(L, 1);
            return this->types[type](m);
        });

    this->RegisterFunction("LCCP_DeleteNode", [this](LightCanvas::ScriptManager*)
        {

            //Obtain the node and clear it from his parent.
            //If the node has no parent it means it was a root node and it will no be "Real deleted".
            //You can use the Scene::DeleteNode if you are using scenes.
            return 0;
        });

    /*
    Input Functions
    */
    lua_getglobal(_lua, "Light_Canvas");
    int LC = lua_gettop(_lua);
    lua_getfield(_lua, LC, "Input");
    int LC_input = lua_gettop(_lua);

    SetTableValue("GetButton", [](lua_State* L)
        {
            if (!lua_isnumber(L, 1)) return 0;
            LightCanvas::ScriptManager* m = (LightCanvas::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
            auto input = LightCanvas::EventManager::Instance()->GetController()->GetButton(lua_tointeger(L, 1));
            m->PushValue(input);
            return 1;
        });
    SetTableValue("GetAxis", [](lua_State* L)
        {
            if (!lua_isnumber(L, 1)) return 0;
            LightCanvas::ScriptManager* m = (LightCanvas::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
            auto input = LightCanvas::EventManager::Instance()->GetController()->GetAxisValue(lua_tointeger(L, 1));
            m->PushValue(input);
            return 1;
        });

    lua_settop(_lua, LC_input - 1);

    lua_getfield(_lua, LC, "AssetManager");
    int LC_Asset = lua_gettop(_lua);
    SetTableValue("LoadImage", LoadImage);
    SetTableValue("LoadSoundEffect", LoadSoundEffect);
    SetTableValue("LoadSong", LoadSong);
    lua_settop(_lua, LC_Asset - 1);
    //Vector

    lua_getfield(_lua, LC, "Vector");
    int LC_Vector = lua_gettop(_lua);
    lua_getfield(_lua, LC_Vector, "Add");
    int V_Add = lua_gettop(_lua);
    lua_getfield(_lua, LC_Vector, "Sub");
    int V_Sub = lua_gettop(_lua);
    lua_getfield(_lua, LC_Vector, "Multiply");
    int V_Multiply = lua_gettop(_lua);
    lua_getfield(_lua, LC_Vector, "mt");
    int V_Meta = lua_gettop(_lua);

    luaL_newmetatable(_lua, "Vector");

    lua_pushstring(_lua, "__index");
    lua_pushvalue(_lua, LC_Vector);
    lua_settable(_lua, -3);
    lua_pushstring(_lua, "__add");
    lua_pushvalue(_lua, V_Add);
    lua_settable(_lua, -3);
    lua_pushstring(_lua, "__sub");
    lua_pushvalue(_lua, V_Sub);
    lua_settable(_lua, -3);
    lua_pushstring(_lua, "__mul");
    lua_pushvalue(_lua, V_Multiply);
    lua_settable(_lua, -3);
    lua_pushstring(_lua, "__metatable");
    lua_pushvalue(_lua, V_Meta);
    lua_settable(_lua, -3);
    lua_settop(_lua, LC_Vector - 1);


    lua_settop(_lua, LC - 1);

}