#ifndef _SCRIPTMANAGER_H_
#define _SCRIPTMANAGER_H_
#include <lua/lua.hpp>
#include <string>
#include <map>
#include <functional>
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

        int PushValue(float value)
        {
            lua_pushnumber(_lua, value);
            return 1;
        }
        int PushValue(lua_CFunction value)
        {
            lua_pushcfunction(_lua, value);
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
            lua_pushcfunction(_lua, value);
            return 1 + PushValue(args...);
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

        /**
         * Adds a function to the lua virtual machine so it can call c/c++ code.
         */
        void RegisterFunction(const std::string& name, lua_CFunction function);
        void RegisterFunction(const std::string& name, std::function<int(ScriptManager* scriptManager)>);

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

        void Close();

    protected:
        /**
         * Opens the conection with the lua virtual machine.
         */
        std::map<std::string, std::function<int(ScriptManager* scriptManager)>> functionMap;
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