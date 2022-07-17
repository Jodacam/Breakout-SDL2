#ifndef _SCRIPTMANAGER_H_
#define _SCRIPTMANAGER_H_
#include "../math/Vector.h"
#include "../events/EventManager.h"
#include <lua/lua.hpp>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <any>
namespace GameEngine
{
    class ScriptManager
    {
    public:
        /**
         * Executes a command on lua. Returns false on error. Check GetError function to get the log.
         */
        bool ExecuteCommand(const std::string& command);
        /**
         * Executes a file as an scripts. Returns false on error. Check GetError funtion to get the log.
         */
        bool ExecuteFile(const std::string& path);
        /**
         * Loads a file into the lua virtual machine memory. Usefull when used with defined functions.
         */
        bool LoadFile(const std::string& path);

        /**
         * @brief Calls a function on the lua virtual machine.
         * @param function The function name
         */
        bool CallFunction(const std::string& function);
        /**
         * @brief Calls a function on the lua virtual machine.
         * @param function The function name
         * @tparam ...Targs Args passed down to the function as new values.
         */
        template <typename... Targs>
        bool CallFunction(const std::string& function, Targs... args)
        {

            int return_code = lua_getglobal(_lua, function.c_str());

            if (!lua_isfunction(_lua, -1))
            {
                _error = lua_tostring(_lua, -1);
                return false;
            }
            int arg_number = PushValue(args...);

            return_code = lua_pcall(_lua, arg_number, 0, 0);

            if (return_code != LUA_OK)
            {
                // Obtain the error from the pile.
                _error = lua_tostring(_lua, -1);
                return false;
            }

            return true;
        }

        /**
         * @brief Calls a function on the lua virtual machine. The function must be inside a table
         * @param function The table name
         * @param function The function name
         * @tparam ...Targs Args passed down to the function as new values.
         */
        template <typename... Targs>
        bool CallTableFunction(const std::string& table, const std::string& function, Targs... args)
        {

            int return_code = lua_getglobal(_lua, table.c_str());

            if (!lua_istable(_lua, -1)) {
                _error = "NOTTABLE";
                return false;
            }

            int top = lua_gettop(_lua);

            lua_getfield(_lua, top, function.c_str());

            if (!lua_isfunction(_lua, -1))
            {
                _error = lua_tostring(_lua, -1);
                return false;
            }
            int arg_number = PushValue(args...);

            return_code = lua_pcall(_lua, arg_number, 0, 0);

            if (return_code != LUA_OK)
            {
                // Obtain the error from the pile.
                _error = lua_tostring(_lua, -1);
                return false;
            }

            //Clean the stack.
            lua_settop(_lua, (top - 1));

            return true;
        }

        template <typename T>
        T* CreateUserData()
        {
            T* data = (T*)lua_newuserdata(_lua, sizeof(T));
            return data;
        }

        /**
         * @brief Push a value into the lua stack. Is usefull for function calls.
         *
         */
        template <typename T>
        int PushValue(T* value)
        {
            lua_pushlightuserdata(_lua, value);
            return 1;
        }

        template <typename T, typename... Targs>
        int PushValue(T* value, Targs... args)
        {
            lua_pushlightuserdata(_lua, value);
            return 1 + PushValue(args...);
        }

#pragma region Value PushValue
        /**
         * @brief Push a int into the stack
         *
         * @param value
         * @return int
         */
        int PushValue(int value)
        {
            lua_pushinteger(_lua, value);
            return 1;
        }
        int PushValue(const char* value)
        {
            lua_pushstring(_lua, value);
            return 1;
        }
        int PushValue(const std::string& value)
        {
            lua_pushstring(_lua, value.c_str());
            return 1;
        }
        int PushValue(bool value) { 
            lua_pushboolean(_lua, value);
            return 1;
        }
        int PushValue(float value)
        {
            lua_pushnumber(_lua, value);
            return 1;
        }
        int PushValue(const GameEngine::GameButton& value) {
            lua_newtable(_lua);
            SetTableValue("isPressed", value.isPressed);
            SetTableValue("pressed", value.pressed);
            SetTableValue("released", value.released);
            SetTableValue("wasPressed", value.wasPressed);
            return 1;
        }
        /**
         * @brief Push a c function into the stack. The instance of Scene manager is alwais added as a closure to the function itself.
         * You can get it with : (GameEngine::ScriptManager*)lua_touserdata(L, lua_upvalueindex(1));
        */
        int PushValue(lua_CFunction value)
        {
            int arguments = PushValue(this);
            lua_pushcclosure(_lua, value, arguments);
            return 1;
        }
        /**
         * @brief Push a GameEngine::Vector into the stack. It is pushed as a table with x and y params.
         *
         * @param value
         * @return int
         */
        int PushValue(Vector value) {
            lua_newtable(_lua);

            SetTableValue("x", value.x);
            SetTableValue("y", value.y);
            luaL_setmetatable(_lua, "Vector");
            return 1;
        }
        template <typename... Targs>
        int PushValue(int value, Targs... args)
        {
            lua_pushinteger(_lua, value);
            return 1 + PushValue(args...);
        }
        template <typename... Targs>
        int PushValue(const std::string& value, Targs... args)
        {
            lua_pushstring(_lua, value.c_str());
            return 1 + PushValue(args...);
        }

        template <typename... Targs>
        int PushValue(const char* value, Targs... args)
        {
            lua_pushstring(_lua, value);
            return 1 + PushValue(args...);
        }
        template <typename... Targs>
        int PushValue(float value, Targs... args)
        {
            lua_pushnumber(_lua, value);
            return 1 + PushValue(args...);
        }
        template <typename... Targs>
        int PushValue(lua_CFunction value, Targs... args)
        {
            return PushValue(value) + PushValue(args...);
        }
        template<typename... Targs>
        int PushValue(Vector value, Targs... args) {
            return PushValue(value) + PushValue(args...);
        }

        /***
         * @brief Push a new function into the stack. You can define a custom closure.
         * Be aware, the scene manager is alwais added as a closure to functions in order to have easy access to it.
         * Using this method with lua_CFuntions as a closure can result in undefined behavior. Each function will use the last arguments as their own closures.
         * Be careful
         */
        template <typename... Targs>
        int PushFunction(lua_CFunction function, Targs... closure) {
            return PushValue(closure...) + PushValue(function);
        }
#pragma endregion

        /**
         * @brief Gets a global value from the global stack.
         */
        template <typename T>
        T* GetGlobalUserData(const std::string& name)
        {
            int a = lua_getglobal(_lua, name.c_str());
            if (!lua_isuserdata(_lua, -1))
                return nullptr;
            auto data = static_cast<T*>(lua_touserdata(_lua, -1));
            return (data);
        };

#pragma region Value Getters.

        int GetGlobalInteger(const std::string& name)
        {
            int a = lua_getglobal(_lua, name.c_str());

            if (a != LUA_TNUMBER)
                return 0;

            return lua_tointeger(_lua, -1);
        }
        const char* GetGlobalString(const std::string& name)
        {
            int a = lua_getglobal(_lua, name.c_str());

            if (a != LUA_TSTRING)
                return nullptr;

            return lua_tostring(_lua, -1);
        }

        bool GetGlobalBoolean(const std::string& name)
        {
            int a = lua_getglobal(_lua, name.c_str());
            if (a != LUA_TBOOLEAN)
                return false;
            return lua_toboolean(_lua, -1);
        }
        float GetGlobalNumber(const std::string& name)
        {
            int a = lua_getglobal(_lua, name.c_str());
            if (a != LUA_TNUMBER)
                return 0.0f;
            return lua_tonumber(_lua, -1);
        }

#pragma endregion

#pragma region Table Modifiers
        template <typename T>
        int SetTableValue(const std::string& name, T value) {
            PushValue(value);
            lua_setfield(_lua, -2, name.c_str());
            return 0;
        }

        /**
         * @brief Sets a Function into a key in a Lua Table
         *
         * @tparam Targs
         * @param name Function name
         * @param function C Function to use
         * @param closure The context of the function. You can treat it like the [] in the lamba.
         * @return int
         */
        template<typename... Targs>
        int SetTableFunction(const std::string& name, lua_CFunction function, Targs... closure) {
            PushFunction(function, closure...);
            lua_setfield(_lua, -2, name.c_str());
            return 0;
        }

        template<typename... Targs>
        int CreateGlobalTable(const std::string& name, Targs... args) {
            lua_newtable(_lua);
            lua_setglobal(_lua, name.c_str());
            int index = lua_gettop(_lua);
            return index;
        }

        int PushTable() {
            return 1;
        }
#pragma endregion
        /**
         * @brief Adds a function to the lua virtual machine so it can call c/c++ code.
         *
         * @param name The function name.
         * @param function The function itself. Due to how lua works only c lambdas are allowed.
         */
        void RegisterFunction(const std::string& name, lua_CFunction function);
        void RegisterFunction(const std::string& name, std::function<int(ScriptManager* scriptManager)> function);
        void RegisterNodeFunction(const std::string& node_name, std::function<int(ScriptManager* scriptManager)> fn);

        inline const std::string GetError()
        {
            return _error;
        }
        ScriptManager()
        {
            this->open();
        };
        ~ScriptManager()
        {
            this->Close();
        };

        /**
         * @brief Returns the lua_State associated with this Script Manager
         */
        inline lua_State* GetInternalVM() { return _lua; }

        /**
         * @brief Register basic functionality like Node types and basic functions no related to scenes.
        */
        void RegisterBasics();

        void Close();

    protected:
        /**
         * Opens the conection with the lua virtual machine.
         */
        std::map<std::string, std::function<int(ScriptManager* scriptManager)>> functionMap;
        std::vector<std::function<int(ScriptManager* scriptManager)>> types;
        int CallInternalFunction(const std::string& name) {
            return functionMap[name](this);
        }
        bool open();

        std::string _error = "";
        lua_State* _lua;

        // Functions calls.
    };

}
#endif //